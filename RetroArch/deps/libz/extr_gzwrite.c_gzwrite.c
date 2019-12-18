#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* z_streamp ;
typedef  char const* voidpc ;
typedef  TYPE_3__* gz_statep ;
typedef  int /*<<< orphan*/ * gzFile ;
struct TYPE_8__ {unsigned int pos; } ;
struct TYPE_9__ {scalar_t__ avail_in; scalar_t__ next_in; } ;
struct TYPE_10__ {scalar_t__ mode; scalar_t__ err; scalar_t__ size; scalar_t__ in; TYPE_1__ x; int /*<<< orphan*/  skip; scalar_t__ seek; TYPE_2__ strm; } ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 scalar_t__ GZ_WRITE ; 
 int /*<<< orphan*/  Z_DATA_ERROR ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 scalar_t__ Z_OK ; 
 int gz_comp (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gz_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int gz_init (TYPE_3__*) ; 
 int gz_zero (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,unsigned int) ; 

int gzwrite(gzFile file, voidpc buf, unsigned len)
{
    unsigned put = len;
    gz_statep state;
    z_streamp strm;

    /* get internal structure */
    if (file == NULL)
        return 0;
    state = (gz_statep)file;
    strm = &(state->strm);

    /* check that we're writing and that there's no error */
    if (state->mode != GZ_WRITE || state->err != Z_OK)
        return 0;

    /* since an int is returned, make sure len fits in one, otherwise return
       with an error (this avoids the flaw in the interface) */
    if ((int)len < 0) {
        gz_error(state, Z_DATA_ERROR, "requested length does not fit in int");
        return 0;
    }

    /* if len is zero, avoid unnecessary operations */
    if (len == 0)
        return 0;

    /* allocate memory if this is the first time through */
    if (state->size == 0 && gz_init(state) == -1)
        return 0;

    /* check for seek request */
    if (state->seek) {
        state->seek = 0;
        if (gz_zero(state, state->skip) == -1)
            return 0;
    }

    /* for small len, copy to input buffer, otherwise compress directly */
    if (len < state->size) {
        /* copy to input buffer, compress when full */
        do {
            unsigned have, copy;

            if (strm->avail_in == 0)
                strm->next_in = state->in;
            have = (unsigned)((strm->next_in + strm->avail_in) - state->in);
            copy = state->size - have;
            if (copy > len)
                copy = len;
            memcpy(state->in + have, buf, copy);
            strm->avail_in += copy;
            state->x.pos += copy;
            buf = (const char *)buf + copy;
            len -= copy;
            if (len && gz_comp(state, Z_NO_FLUSH) == -1)
                return 0;
        } while (len);
    }
    else {
        /* consume whatever's left in the input buffer */
        if (strm->avail_in && gz_comp(state, Z_NO_FLUSH) == -1)
            return 0;

        /* directly compress user buffer to file */
        strm->avail_in = len;
        strm->next_in = (Bytef *)buf;
        state->x.pos += len;
        if (gz_comp(state, Z_NO_FLUSH) == -1)
            return 0;
    }

    /* input was all buffered or compressed (put will fit in int) */
    return (int)put;
}
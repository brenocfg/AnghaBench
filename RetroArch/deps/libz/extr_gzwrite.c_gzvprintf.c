#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* z_streamp ;
typedef  int /*<<< orphan*/  va_list ;
typedef  TYPE_3__* gz_statep ;
typedef  int /*<<< orphan*/ * gzFile ;
struct TYPE_7__ {int pos; } ;
struct TYPE_8__ {unsigned int avail_in; scalar_t__* next_in; } ;
struct TYPE_9__ {scalar_t__ mode; scalar_t__ err; scalar_t__* in; TYPE_1__ x; scalar_t__ size; int /*<<< orphan*/  skip; scalar_t__ seek; TYPE_2__ strm; } ;

/* Variables and functions */
 scalar_t__ GZ_WRITE ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 scalar_t__ Z_OK ; 
 int gz_comp (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int gz_init (TYPE_3__*) ; 
 int gz_zero (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int vsprintf (char*,char const*,int /*<<< orphan*/ ) ; 

int gzvprintf(gzFile file, const char *format, va_list va)
{
    int size, len;
    gz_statep state;
    z_streamp strm;

    /* get internal structure */
    if (file == NULL)
        return -1;
    state = (gz_statep)file;
    strm = &(state->strm);

    /* check that we're writing and that there's no error */
    if (state->mode != GZ_WRITE || state->err != Z_OK)
        return 0;

    /* make sure we have some buffer space */
    if (state->size == 0 && gz_init(state) == -1)
        return 0;

    /* check for seek request */
    if (state->seek) {
        state->seek = 0;
        if (gz_zero(state, state->skip) == -1)
            return 0;
    }

    /* consume whatever's left in the input buffer */
    if (strm->avail_in && gz_comp(state, Z_NO_FLUSH) == -1)
        return 0;

    /* do the printf() into the input buffer, put length in len */
    size = (int)(state->size);
    state->in[size - 1] = 0;
#ifdef NO_vsnprintf
#  ifdef HAS_vsprintf_void
    (void)vsprintf((char *)(state->in), format, va);
    for (len = 0; len < size; len++)
        if (state->in[len] == 0) break;
#  else
    len = vsprintf((char *)(state->in), format, va);
#  endif
#else
#  ifdef HAS_vsnprintf_void
    (void)vsnprintf((char *)(state->in), size, format, va);
    len = strlen((char *)(state->in));
#  else
    len = vsnprintf((char *)(state->in), size, format, va);
#  endif
#endif

    /* check that printf() results fit in buffer */
    if (len <= 0 || len >= (int)size || state->in[size - 1] != 0)
        return 0;

    /* update buffer and position, defer compression until needed */
    strm->avail_in = (unsigned)len;
    strm->next_in = state->in;
    state->x.pos += len;
    return len;
}
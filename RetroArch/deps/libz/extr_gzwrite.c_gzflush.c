#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gz_statep ;
typedef  int /*<<< orphan*/ * gzFile ;
struct TYPE_4__ {scalar_t__ mode; scalar_t__ err; int /*<<< orphan*/  skip; scalar_t__ seek; } ;

/* Variables and functions */
 scalar_t__ GZ_WRITE ; 
 int Z_FINISH ; 
 scalar_t__ Z_OK ; 
 int Z_STREAM_ERROR ; 
 int /*<<< orphan*/  gz_comp (TYPE_1__*,int) ; 
 int gz_zero (TYPE_1__*,int /*<<< orphan*/ ) ; 

int gzflush(gzFile file, int flush)
{
    gz_statep state;

    /* get internal structure */
    if (file == NULL)
        return -1;
    state = (gz_statep)file;

    /* check that we're writing and that there's no error */
    if (state->mode != GZ_WRITE || state->err != Z_OK)
        return Z_STREAM_ERROR;

    /* check flush parameter */
    if (flush < 0 || flush > Z_FINISH)
        return Z_STREAM_ERROR;

    /* check for seek request */
    if (state->seek) {
        state->seek = 0;
        if (gz_zero(state, state->skip) == -1)
            return -1;
    }

    /* compress remaining data with requested flush */
    gz_comp(state, flush);
    return state->err;
}
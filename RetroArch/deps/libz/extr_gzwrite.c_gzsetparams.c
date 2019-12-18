#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
typedef  TYPE_2__* gz_statep ;
typedef  int /*<<< orphan*/ * gzFile ;
struct TYPE_6__ {scalar_t__ avail_in; } ;
struct TYPE_7__ {scalar_t__ mode; scalar_t__ err; int level; int strategy; scalar_t__ size; int /*<<< orphan*/  skip; scalar_t__ seek; TYPE_1__ strm; } ;

/* Variables and functions */
 scalar_t__ GZ_WRITE ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  Z_PARTIAL_FLUSH ; 
 int Z_STREAM_ERROR ; 
 int /*<<< orphan*/  deflateParams (TYPE_1__*,int,int) ; 
 int gz_comp (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int gz_zero (TYPE_2__*,int /*<<< orphan*/ ) ; 

int gzsetparams(gzFile file, int level, int strategy)
{
    gz_statep state;
    z_streamp strm;

    /* get internal structure */
    if (file == NULL)
        return Z_STREAM_ERROR;
    state = (gz_statep)file;
    strm = &(state->strm);

    /* check that we're writing and that there's no error */
    if (state->mode != GZ_WRITE || state->err != Z_OK)
        return Z_STREAM_ERROR;

    /* if no change is requested, then do nothing */
    if (level == state->level && strategy == state->strategy)
        return Z_OK;

    /* check for seek request */
    if (state->seek) {
        state->seek = 0;
        if (gz_zero(state, state->skip) == -1)
            return -1;
    }

    /* change compression parameters for subsequent input */
    if (state->size) {
        /* flush previous input with previous parameters before changing */
        if (strm->avail_in && gz_comp(state, Z_PARTIAL_FLUSH) == -1)
            return state->err;
        deflateParams(strm, level, strategy);
    }
    state->level = level;
    state->strategy = strategy;
    return Z_OK;
}
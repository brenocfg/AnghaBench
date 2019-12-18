#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
struct inflate_state {unsigned int dmax; unsigned int wsize; unsigned int wbits; scalar_t__ whave; scalar_t__ write; int /*<<< orphan*/  codes; int /*<<< orphan*/  next; int /*<<< orphan*/  distcode; int /*<<< orphan*/  lencode; scalar_t__ bits; scalar_t__ hold; scalar_t__ havedict; scalar_t__ last; int /*<<< orphan*/  mode; scalar_t__ total; } ;
struct TYPE_3__ {int adler; int /*<<< orphan*/ * msg; scalar_t__ total_out; scalar_t__ total_in; int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEAD ; 
 int Z_OK ; 
 int Z_STREAM_ERROR ; 

int zlib_inflateReset(z_streamp strm)
{
    struct inflate_state *state;

    if (strm == NULL || strm->state == NULL) return Z_STREAM_ERROR;
    state = (struct inflate_state *)strm->state;
    strm->total_in = strm->total_out = state->total = 0;
    strm->msg = NULL;
    strm->adler = 1;        /* to support ill-conceived Java test suite */
    state->mode = HEAD;
    state->last = 0;
    state->havedict = 0;
    state->dmax = 32768U;
    state->hold = 0;
    state->bits = 0;
    state->lencode = state->distcode = state->next = state->codes;

    /* Initialise Window */
    state->wsize = 1U << state->wbits;
    state->write = 0;
    state->whave = 0;

    return Z_OK;
}
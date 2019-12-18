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
struct TYPE_3__ {int twonear; int near; int range; int maxval; int qbpp; int bpp; int limit; int* A; int* N; } ;
typedef  TYPE_1__ JLSState ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int av_log2 (int) ; 

void ff_jpegls_init_state(JLSState *state)
{
    int i;

    state->twonear = state->near * 2 + 1;
    state->range   = (state->maxval + state->twonear - 1) / state->twonear + 1;

    // QBPP = ceil(log2(RANGE))
    for (state->qbpp = 0; (1 << state->qbpp) < state->range; state->qbpp++)
        ;

    state->bpp   = FFMAX(av_log2(state->maxval) + 1, 2);
    state->limit = 2*(state->bpp + FFMAX(state->bpp, 8)) - state->qbpp;

    for (i = 0; i < 367; i++) {
        state->A[i] = FFMAX(state->range + 32 >> 6, 2);
        state->N[i] = 1;
    }
}
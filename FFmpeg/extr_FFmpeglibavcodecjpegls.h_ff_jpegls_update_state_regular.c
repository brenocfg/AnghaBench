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
struct TYPE_4__ {int* A; int twonear; int* B; int* N; int* C; } ;
typedef  TYPE_1__ JLSState ;

/* Variables and functions */
 int FFABS (int) ; 
 int FFMAX (int,int) ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_jpegls_downscale_state (TYPE_1__*,int) ; 

__attribute__((used)) static inline int ff_jpegls_update_state_regular(JLSState *state,
                                                 int Q, int err)
{
    if(FFABS(err) > 0xFFFF)
        return -0x10000;
    state->A[Q] += FFABS(err);
    err         *= state->twonear;
    state->B[Q] += err;

    ff_jpegls_downscale_state(state, Q);

    if (state->B[Q] <= -state->N[Q]) {
        state->B[Q] = FFMAX(state->B[Q] + state->N[Q], 1 - state->N[Q]);
        if (state->C[Q] > -128)
            state->C[Q]--;
    } else if (state->B[Q] > 0) {
        state->B[Q] = FFMIN(state->B[Q] - state->N[Q], 0);
        if (state->C[Q] < 127)
            state->C[Q]++;
    }

    return err;
}
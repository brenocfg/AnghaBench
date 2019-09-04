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
struct TYPE_3__ {size_t* run_index; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ JLSState ;

/* Variables and functions */
 int* ff_log2_run ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void ls_encode_run(JLSState *state, PutBitContext *pb, int run,
                                 int comp, int trail)
{
    while (run >= (1 << ff_log2_run[state->run_index[comp]])) {
        put_bits(pb, 1, 1);
        run -= 1 << ff_log2_run[state->run_index[comp]];
        if (state->run_index[comp] < 31)
            state->run_index[comp]++;
    }
    /* if hit EOL, encode another full run, else encode aborted run */
    if (!trail && run) {
        put_bits(pb, 1, 1);
    } else if (trail) {
        put_bits(pb, 1, 0);
        if (ff_log2_run[state->run_index[comp]])
            put_bits(pb, ff_log2_run[state->run_index[comp]], run);
    }
}
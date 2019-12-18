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
struct TYPE_4__ {int count; int error_sum; int drift; int /*<<< orphan*/  bias; } ;
typedef  TYPE_1__ VlcState ;
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  ff_dlog (int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ ,int,int,int,int) ; 
 int fold (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_sr_golomb (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  update_vlc_state (TYPE_1__* const,int) ; 

__attribute__((used)) static inline void put_vlc_symbol(PutBitContext *pb, VlcState *const state,
                                  int v, int bits)
{
    int i, k, code;
    v = fold(v - state->bias, bits);

    i = state->count;
    k = 0;
    while (i < state->error_sum) { // FIXME: optimize
        k++;
        i += i;
    }

    av_assert2(k <= 13);

    code = v ^ ((2 * state->drift + state->count) >> 31);

    ff_dlog(NULL, "v:%d/%d bias:%d error:%d drift:%d count:%d k:%d\n", v, code,
            state->bias, state->error_sum, state->drift, state->count, k);
    set_sr_golomb(pb, code, k, 12, bits);

    update_vlc_state(state, v);
}
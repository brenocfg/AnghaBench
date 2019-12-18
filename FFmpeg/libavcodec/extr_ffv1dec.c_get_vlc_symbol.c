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
struct TYPE_4__ {int count; int error_sum; int drift; scalar_t__ bias; } ;
typedef  TYPE_1__ VlcState ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_dlog (int /*<<< orphan*/ *,char*,int,scalar_t__,int,int,int,int) ; 
 int fold (scalar_t__,int) ; 
 int get_sr_golomb (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  update_vlc_state (TYPE_1__* const,int) ; 

__attribute__((used)) static inline int get_vlc_symbol(GetBitContext *gb, VlcState *const state,
                                 int bits)
{
    int k, i, v, ret;

    i = state->count;
    k = 0;
    while (i < state->error_sum) { // FIXME: optimize
        k++;
        i += i;
    }

    v = get_sr_golomb(gb, k, 12, bits);
    ff_dlog(NULL, "v:%d bias:%d error:%d drift:%d count:%d k:%d",
            v, state->bias, state->error_sum, state->drift, state->count, k);

    v ^= ((2 * state->drift + state->count) >> 31);

    ret = fold(v + state->bias, bits);

    update_vlc_state(state, v);

    return ret;
}
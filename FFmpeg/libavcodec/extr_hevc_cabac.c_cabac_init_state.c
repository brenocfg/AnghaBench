#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int slice_type; int /*<<< orphan*/  slice_qp; scalar_t__ cabac_init_flag; } ;
struct TYPE_7__ {TYPE_2__* HEVClc; TYPE_1__ sh; } ;
struct TYPE_6__ {int* cabac_state; scalar_t__* stat_coeff; } ;
typedef  TYPE_3__ HEVCContext ;

/* Variables and functions */
 int HEVC_CONTEXTS ; 
 int HEVC_SLICE_I ; 
 int av_clip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int** init_values ; 

__attribute__((used)) static void cabac_init_state(HEVCContext *s)
{
    int init_type = 2 - s->sh.slice_type;
    int i;

    if (s->sh.cabac_init_flag && s->sh.slice_type != HEVC_SLICE_I)
        init_type ^= 3;

    for (i = 0; i < HEVC_CONTEXTS; i++) {
        int init_value = init_values[init_type][i];
        int m = (init_value >> 4) * 5 - 45;
        int n = ((init_value & 15) << 3) - 16;
        int pre = 2 * (((m * av_clip(s->sh.slice_qp, 0, 51)) >> 4) + n) - 127;

        pre ^= pre >> 31;
        if (pre > 124)
            pre = 124 + (pre & 1);
        s->HEVClc->cabac_state[i] = pre;
    }

    for (i = 0; i < 4; i++)
        s->HEVClc->stat_coeff[i] = 0;
}
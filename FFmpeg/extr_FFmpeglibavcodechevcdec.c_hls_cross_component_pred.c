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
struct TYPE_9__ {TYPE_2__* HEVClc; } ;
struct TYPE_7__ {int res_scale_val; } ;
struct TYPE_8__ {TYPE_1__ tu; } ;
typedef  TYPE_2__ HEVCLocalContext ;
typedef  TYPE_3__ HEVCContext ;

/* Variables and functions */
 int ff_hevc_log2_res_scale_abs (TYPE_3__*,int) ; 
 int ff_hevc_res_scale_sign_flag (TYPE_3__*,int) ; 

__attribute__((used)) static int hls_cross_component_pred(HEVCContext *s, int idx) {
    HEVCLocalContext *lc    = s->HEVClc;
    int log2_res_scale_abs_plus1 = ff_hevc_log2_res_scale_abs(s, idx);

    if (log2_res_scale_abs_plus1 !=  0) {
        int res_scale_sign_flag = ff_hevc_res_scale_sign_flag(s, idx);
        lc->tu.res_scale_val = (1 << (log2_res_scale_abs_plus1 - 1)) *
                               (1 - 2 * res_scale_sign_flag);
    } else {
        lc->tu.res_scale_val = 0;
    }


    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  HEVCContext ;

/* Variables and functions */
 int GET_CABAC (scalar_t__) ; 
 size_t RES_SCALE_SIGN_FLAG ; 
 scalar_t__* elem_offset ; 

int ff_hevc_res_scale_sign_flag(HEVCContext *s, int idx) {
    return GET_CABAC(elem_offset[RES_SCALE_SIGN_FLAG] + idx);
}
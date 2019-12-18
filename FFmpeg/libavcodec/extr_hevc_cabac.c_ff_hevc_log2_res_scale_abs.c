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
 scalar_t__ GET_CABAC (scalar_t__) ; 
 size_t LOG2_RES_SCALE_ABS ; 
 scalar_t__* elem_offset ; 

int ff_hevc_log2_res_scale_abs(HEVCContext *s, int idx) {
    int i =0;

    while (i < 4 && GET_CABAC(elem_offset[LOG2_RES_SCALE_ABS] + 4 * idx + i))
        i++;

    return i;
}
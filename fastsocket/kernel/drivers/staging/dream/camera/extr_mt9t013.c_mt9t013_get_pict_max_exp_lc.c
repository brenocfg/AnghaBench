#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_6__ {scalar_t__ pict_res; } ;
struct TYPE_5__ {TYPE_1__* reg_pat; } ;
struct TYPE_4__ {int frame_length_lines; } ;

/* Variables and functions */
 scalar_t__ QTR_SIZE ; 
 size_t RES_CAPTURE ; 
 size_t RES_PREVIEW ; 
 TYPE_3__* mt9t013_ctrl ; 
 TYPE_2__ mt9t013_regs ; 

__attribute__((used)) static uint32_t mt9t013_get_pict_max_exp_lc(void)
{
	uint16_t snapshot_lines_per_frame;

	if (mt9t013_ctrl->pict_res == QTR_SIZE) {
		snapshot_lines_per_frame =
		mt9t013_regs.reg_pat[RES_PREVIEW].frame_length_lines - 1;
	} else  {
		snapshot_lines_per_frame =
		mt9t013_regs.reg_pat[RES_CAPTURE].frame_length_lines - 1;
	}

	return snapshot_lines_per_frame * 24;
}
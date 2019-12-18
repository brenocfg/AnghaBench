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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {scalar_t__ prev_res; } ;
struct TYPE_5__ {TYPE_1__* reg_pat; } ;
struct TYPE_4__ {int /*<<< orphan*/  line_length_pck; } ;

/* Variables and functions */
 scalar_t__ QTR_SIZE ; 
 size_t RES_CAPTURE ; 
 size_t RES_PREVIEW ; 
 TYPE_3__* mt9p012_ctrl ; 
 TYPE_2__ mt9p012_regs ; 

__attribute__((used)) static uint16_t mt9p012_get_prev_pixels_pl(void)
{
	if (mt9p012_ctrl->prev_res == QTR_SIZE)
		return mt9p012_regs.reg_pat[RES_PREVIEW].line_length_pck;
	else
		return mt9p012_regs.reg_pat[RES_CAPTURE].line_length_pck;
}
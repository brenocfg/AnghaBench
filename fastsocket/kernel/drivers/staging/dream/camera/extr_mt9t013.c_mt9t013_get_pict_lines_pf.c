#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {TYPE_1__* reg_pat; } ;
struct TYPE_3__ {int /*<<< orphan*/  frame_length_lines; } ;

/* Variables and functions */
 size_t RES_CAPTURE ; 
 TYPE_2__ mt9t013_regs ; 

__attribute__((used)) static uint16_t mt9t013_get_pict_lines_pf(void)
{
	return mt9t013_regs.reg_pat[RES_CAPTURE].frame_length_lines;
}
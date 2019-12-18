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
struct TYPE_4__ {TYPE_1__* chip_info; } ;
struct TYPE_3__ {int gfx_chip_name; } ;

/* Variables and functions */
#define  UNICHROME_CX700 128 
 TYPE_2__* viaparinfo ; 

__attribute__((used)) static void dvi_patch_skew_dvp1(void)
{
	switch (viaparinfo->chip_info->gfx_chip_name) {
	case UNICHROME_CX700:
		{
			break;
		}

	default:
		{
			break;
		}
	}
}
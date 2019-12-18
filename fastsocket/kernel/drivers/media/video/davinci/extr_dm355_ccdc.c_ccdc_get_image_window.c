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
struct v4l2_rect {int dummy; } ;
struct TYPE_4__ {struct v4l2_rect win; } ;
struct TYPE_3__ {struct v4l2_rect win; } ;

/* Variables and functions */
 scalar_t__ VPFE_RAW_BAYER ; 
 TYPE_2__ ccdc_hw_params_raw ; 
 TYPE_1__ ccdc_hw_params_ycbcr ; 
 scalar_t__ ccdc_if_type ; 

__attribute__((used)) static void ccdc_get_image_window(struct v4l2_rect *win)
{
	if (ccdc_if_type == VPFE_RAW_BAYER)
		*win = ccdc_hw_params_raw.win;
	else
		*win = ccdc_hw_params_ycbcr.win;
}
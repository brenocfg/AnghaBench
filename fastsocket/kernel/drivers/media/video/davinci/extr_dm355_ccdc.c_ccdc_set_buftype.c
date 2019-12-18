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
typedef  enum ccdc_buftype { ____Placeholder_ccdc_buftype } ccdc_buftype ;
struct TYPE_4__ {int buf_type; } ;
struct TYPE_3__ {int buf_type; } ;

/* Variables and functions */
 scalar_t__ VPFE_RAW_BAYER ; 
 TYPE_2__ ccdc_hw_params_raw ; 
 TYPE_1__ ccdc_hw_params_ycbcr ; 
 scalar_t__ ccdc_if_type ; 

__attribute__((used)) static int ccdc_set_buftype(enum ccdc_buftype buf_type)
{
	if (ccdc_if_type == VPFE_RAW_BAYER)
		ccdc_hw_params_raw.buf_type = buf_type;
	else
		ccdc_hw_params_ycbcr.buf_type = buf_type;
	return 0;
}
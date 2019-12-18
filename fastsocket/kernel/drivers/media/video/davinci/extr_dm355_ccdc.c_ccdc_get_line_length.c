#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ enable; } ;
struct ccdc_config_params_raw {scalar_t__ data_sz; TYPE_1__ alaw; } ;
struct TYPE_7__ {unsigned int width; } ;
struct TYPE_10__ {TYPE_2__ win; struct ccdc_config_params_raw config_params; } ;
struct TYPE_8__ {int width; } ;
struct TYPE_9__ {TYPE_3__ win; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int) ; 
 scalar_t__ CCDC_DATA_8BITS ; 
 scalar_t__ VPFE_RAW_BAYER ; 
 TYPE_5__ ccdc_hw_params_raw ; 
 TYPE_4__ ccdc_hw_params_ycbcr ; 
 scalar_t__ ccdc_if_type ; 

__attribute__((used)) static unsigned int ccdc_get_line_length(void)
{
	struct ccdc_config_params_raw *config_params =
		&ccdc_hw_params_raw.config_params;
	unsigned int len;

	if (ccdc_if_type == VPFE_RAW_BAYER) {
		if ((config_params->alaw.enable) ||
		    (config_params->data_sz == CCDC_DATA_8BITS))
			len = ccdc_hw_params_raw.win.width;
		else
			len = ccdc_hw_params_raw.win.width * 2;
	} else
		len = ccdc_hw_params_ycbcr.win.width * 2;
	return ALIGN(len, 32);
}
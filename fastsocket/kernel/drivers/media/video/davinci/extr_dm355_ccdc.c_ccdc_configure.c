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

/* Variables and functions */
 scalar_t__ VPFE_RAW_BAYER ; 
 int ccdc_config_raw () ; 
 int /*<<< orphan*/  ccdc_config_ycbcr () ; 
 scalar_t__ ccdc_if_type ; 

__attribute__((used)) static int ccdc_configure(void)
{
	if (ccdc_if_type == VPFE_RAW_BAYER)
		return ccdc_config_raw();
	else
		ccdc_config_ycbcr();
	return 0;
}
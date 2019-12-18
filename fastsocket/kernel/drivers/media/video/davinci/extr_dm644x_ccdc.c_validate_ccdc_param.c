#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ gama_wd; scalar_t__ enable; } ;
struct ccdc_config_params_raw {scalar_t__ data_sz; TYPE_1__ alaw; } ;

/* Variables and functions */
 scalar_t__ CCDC_GAMMA_BITS_09_0 ; 
 scalar_t__ CCDC_GAMMA_BITS_15_6 ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int validate_ccdc_param(struct ccdc_config_params_raw *ccdcparam)
{
	if (ccdcparam->alaw.enable) {
		if ((ccdcparam->alaw.gama_wd > CCDC_GAMMA_BITS_09_0) ||
		    (ccdcparam->alaw.gama_wd < CCDC_GAMMA_BITS_15_6) ||
		    (ccdcparam->alaw.gama_wd < ccdcparam->data_sz)) {
			dev_dbg(dev, "\nInvalid data line select");
			return -1;
		}
	}
	return 0;
}
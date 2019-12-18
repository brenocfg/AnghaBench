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
struct vpfe_hw_if_param {int if_type; int /*<<< orphan*/  hdpol; int /*<<< orphan*/  vdpol; } ;
struct TYPE_2__ {int /*<<< orphan*/  hd_pol; int /*<<< orphan*/  vd_pol; } ;

/* Variables and functions */
 int EINVAL ; 
#define  VPFE_BT656 130 
#define  VPFE_YCBCR_SYNC_16 129 
#define  VPFE_YCBCR_SYNC_8 128 
 TYPE_1__ ccdc_hw_params_ycbcr ; 
 int ccdc_if_type ; 

__attribute__((used)) static int ccdc_set_hw_if_params(struct vpfe_hw_if_param *params)
{
	ccdc_if_type = params->if_type;

	switch (params->if_type) {
	case VPFE_BT656:
	case VPFE_YCBCR_SYNC_16:
	case VPFE_YCBCR_SYNC_8:
		ccdc_hw_params_ycbcr.vd_pol = params->vdpol;
		ccdc_hw_params_ycbcr.hd_pol = params->hdpol;
		break;
	default:
		/* TODO add support for raw bayer here */
		return -EINVAL;
	}
	return 0;
}
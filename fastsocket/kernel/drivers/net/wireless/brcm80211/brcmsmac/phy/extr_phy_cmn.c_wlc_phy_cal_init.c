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
struct brcms_phy_pub {int dummy; } ;
struct TYPE_2__ {void (* calinit ) (struct brcms_phy*) ;} ;
struct brcms_phy {int initialized; TYPE_1__ pi_fptr; int /*<<< orphan*/  d11core; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int MCTL_EN_MAC ; 
 scalar_t__ WARN (int,char*) ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 void stub1 (struct brcms_phy*) ; 

void wlc_phy_cal_init(struct brcms_phy_pub *pih)
{
	struct brcms_phy *pi = (struct brcms_phy *) pih;
	void (*cal_init)(struct brcms_phy *) = NULL;

	if (WARN((bcma_read32(pi->d11core, D11REGOFFS(maccontrol)) &
		  MCTL_EN_MAC) != 0, "HW error: MAC enabled during phy cal\n"))
		return;

	if (!pi->initialized) {
		cal_init = pi->pi_fptr.calinit;
		if (cal_init)
			(*cal_init)(pi);

		pi->initialized = true;
	}
}
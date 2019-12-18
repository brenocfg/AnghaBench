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
struct brcms_hardware {int /*<<< orphan*/  corerev; TYPE_1__* wlc; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_HAS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D11CONF ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool brcms_c_isgoodchip(struct brcms_hardware *wlc_hw)
{

	/* reject unsupported corerev */
	if (!CONF_HAS(D11CONF, wlc_hw->corerev)) {
		wiphy_err(wlc_hw->wlc->wiphy, "unsupported core rev %d\n",
			  wlc_hw->corerev);
		return false;
	}

	return true;
}
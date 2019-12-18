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
struct TYPE_2__ {int /*<<< orphan*/  prtad; } ;
struct cphy {TYPE_1__ mdio; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 int t3_phy_reset (struct cphy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aq100x_reset(struct cphy *phy, int wait)
{
	/*
	 * Ignore the caller specified wait time; always wait for the reset to
	 * complete. Can take up to 3s.
	 */
	int err = t3_phy_reset(phy, MDIO_MMD_VEND1, 3000);

	if (err)
		CH_WARN(phy->adapter, "PHY%d: reset failed (0x%x).\n",
			phy->mdio.prtad, err);

	return err;
}
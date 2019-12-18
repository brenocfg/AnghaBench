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
typedef  int /*<<< orphan*/  uint ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {int txpwroverride; int /*<<< orphan*/ * tx_user_target; } ;

/* Variables and functions */

int wlc_phy_txpower_get(struct brcms_phy_pub *ppi, uint *qdbm, bool *override)
{
	struct brcms_phy *pi = (struct brcms_phy *) ppi;

	*qdbm = pi->tx_user_target[0];
	if (override != NULL)
		*override = pi->txpwroverride;
	return 0;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {TYPE_1__* sh; } ;
struct TYPE_2__ {int /*<<< orphan*/  phyrxchain; int /*<<< orphan*/  phytxchain; } ;

/* Variables and functions */

void wlc_phy_stf_chain_get(struct brcms_phy_pub *pih, u8 *txchain, u8 *rxchain)
{
	struct brcms_phy *pi = (struct brcms_phy *) pih;

	*txchain = pi->sh->phytxchain;
	*rxchain = pi->sh->phyrxchain;
}
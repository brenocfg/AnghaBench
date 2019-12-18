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
typedef  void* u8 ;
struct brcms_phy_pub {int dummy; } ;
struct TYPE_3__ {void* phy_corenum; } ;
struct brcms_phy {TYPE_2__* sh; TYPE_1__ pubpi; } ;
struct TYPE_4__ {int /*<<< orphan*/  phyrxchain; void* phytxchain; } ;

/* Variables and functions */
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 scalar_t__ hweight8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_rxcore_setstate_nphy (struct brcms_phy_pub*,void*) ; 

void wlc_phy_stf_chain_set(struct brcms_phy_pub *pih, u8 txchain, u8 rxchain)
{
	struct brcms_phy *pi = (struct brcms_phy *) pih;

	pi->sh->phytxchain = txchain;

	if (ISNPHY(pi))
		wlc_phy_rxcore_setstate_nphy(pih, rxchain);

	pi->pubpi.phy_corenum = (u8)hweight8(pi->sh->phyrxchain);
}
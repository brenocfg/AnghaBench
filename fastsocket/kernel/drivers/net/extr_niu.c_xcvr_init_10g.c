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
typedef  int /*<<< orphan*/  u64 ;
struct niu {size_t port; TYPE_2__* parent; } ;
struct TYPE_3__ {int** phy_id; } ;
struct TYPE_4__ {TYPE_1__ phy_probe_info; int /*<<< orphan*/  port_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIF_CONFIG ; 
 int /*<<< orphan*/  MIF_CONFIG_INDIRECT_MODE ; 
 int NIU_PHY_ID_MASK ; 
#define  NIU_PHY_ID_MRVL88X2011 128 
 int /*<<< orphan*/  XMAC_CONFIG ; 
 int /*<<< orphan*/  XMAC_CONFIG_FORCE_LED_ON ; 
 int /*<<< orphan*/  XMAC_CONFIG_LED_POLARITY ; 
 int /*<<< orphan*/  nr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr64_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_decode (int /*<<< orphan*/ ,size_t) ; 
 int xcvr_init_10g_bcm8704 (struct niu*) ; 
 int xcvr_init_10g_mrvl88x2011 (struct niu*) ; 

__attribute__((used)) static int xcvr_init_10g(struct niu *np)
{
	int phy_id, err;
	u64 val;

	val = nr64_mac(XMAC_CONFIG);
	val &= ~XMAC_CONFIG_LED_POLARITY;
	val |= XMAC_CONFIG_FORCE_LED_ON;
	nw64_mac(XMAC_CONFIG, val);

	/* XXX shared resource, lock parent XXX */
	val = nr64(MIF_CONFIG);
	val |= MIF_CONFIG_INDIRECT_MODE;
	nw64(MIF_CONFIG, val);

	phy_id = phy_decode(np->parent->port_phy, np->port);
	phy_id = np->parent->phy_probe_info.phy_id[phy_id][np->port];

	/* handle different phy types */
	switch (phy_id & NIU_PHY_ID_MASK) {
	case NIU_PHY_ID_MRVL88X2011:
		err = xcvr_init_10g_mrvl88x2011(np);
		break;

	default: /* bcom 8704 */
		err = xcvr_init_10g_bcm8704(np);
		break;
	}

	return 0;
}
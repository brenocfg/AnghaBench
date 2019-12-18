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
typedef  int u32 ;
struct bcm_enet_priv {int dummy; } ;

/* Variables and functions */
 int ENET_MIIDATA_OP_READ_MASK ; 
 int ENET_MIIDATA_PHYID_SHIFT ; 
 int /*<<< orphan*/  ENET_MIIDATA_REG ; 
 int ENET_MIIDATA_REG_SHIFT ; 
 int ENET_MIIDATA_TA_SHIFT ; 
 scalar_t__ do_mdio_op (struct bcm_enet_priv*,int) ; 
 int enet_readl (struct bcm_enet_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_enet_mdio_read(struct bcm_enet_priv *priv, int mii_id,
			      int regnum)
{
	u32 tmp, val;

	tmp = regnum << ENET_MIIDATA_REG_SHIFT;
	tmp |= 0x2 << ENET_MIIDATA_TA_SHIFT;
	tmp |= mii_id << ENET_MIIDATA_PHYID_SHIFT;
	tmp |= ENET_MIIDATA_OP_READ_MASK;

	if (do_mdio_op(priv, tmp))
		return -1;

	val = enet_readl(priv, ENET_MIIDATA_REG);
	val &= 0xffff;
	return val;
}
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
typedef  int u16 ;
struct bcm_enet_priv {int dummy; } ;

/* Variables and functions */
 int ENET_MIIDATA_DATA_SHIFT ; 
 int ENET_MIIDATA_OP_WRITE_MASK ; 
 int ENET_MIIDATA_PHYID_SHIFT ; 
 int ENET_MIIDATA_REG_SHIFT ; 
 int ENET_MIIDATA_TA_SHIFT ; 
 int /*<<< orphan*/  do_mdio_op (struct bcm_enet_priv*,int) ; 

__attribute__((used)) static int bcm_enet_mdio_write(struct bcm_enet_priv *priv, int mii_id,
			       int regnum, u16 value)
{
	u32 tmp;

	tmp = (value & 0xffff) << ENET_MIIDATA_DATA_SHIFT;
	tmp |= 0x2 << ENET_MIIDATA_TA_SHIFT;
	tmp |= regnum << ENET_MIIDATA_REG_SHIFT;
	tmp |= mii_id << ENET_MIIDATA_PHYID_SHIFT;
	tmp |= ENET_MIIDATA_OP_WRITE_MASK;

	(void)do_mdio_op(priv, tmp);
	return 0;
}
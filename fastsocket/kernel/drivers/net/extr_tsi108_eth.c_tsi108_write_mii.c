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
typedef  int u16 ;
struct tsi108_prv_data {int phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSI108_MAC_MII_ADDR ; 
 int TSI108_MAC_MII_ADDR_PHY ; 
 int TSI108_MAC_MII_ADDR_REG ; 
 int /*<<< orphan*/  TSI108_MAC_MII_DATAOUT ; 
 int /*<<< orphan*/  TSI108_MAC_MII_IND ; 
 int TSI108_MAC_MII_IND_BUSY ; 
 int TSI_READ_PHY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSI_WRITE_PHY (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tsi108_write_mii(struct tsi108_prv_data *data,
				int reg, u16 val)
{
	unsigned i = 100;
	TSI_WRITE_PHY(TSI108_MAC_MII_ADDR,
				(data->phy << TSI108_MAC_MII_ADDR_PHY) |
				(reg << TSI108_MAC_MII_ADDR_REG));
	TSI_WRITE_PHY(TSI108_MAC_MII_DATAOUT, val);
	while (i--) {
		if(!(TSI_READ_PHY(TSI108_MAC_MII_IND) &
			TSI108_MAC_MII_IND_BUSY))
			break;
		udelay(10);
	}
}
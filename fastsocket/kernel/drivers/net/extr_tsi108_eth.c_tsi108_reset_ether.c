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
struct tsi108_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSI108_EC_PORTCTRL ; 
 int TSI108_EC_PORTCTRL_STATRST ; 
 int /*<<< orphan*/  TSI108_EC_RXCFG ; 
 int TSI108_EC_RXCFG_RST ; 
 int /*<<< orphan*/  TSI108_EC_TXCFG ; 
 int TSI108_EC_TXCFG_RST ; 
 int /*<<< orphan*/  TSI108_MAC_CFG1 ; 
 int TSI108_MAC_CFG1_SOFTRST ; 
 int /*<<< orphan*/  TSI108_MAC_MII_MGMT_CFG ; 
 int TSI108_MAC_MII_MGMT_CLK ; 
 int TSI108_MAC_MII_MGMT_RST ; 
 int TSI_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSI_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tsi108_reset_ether(struct tsi108_prv_data * data)
{
	TSI_WRITE(TSI108_MAC_CFG1, TSI108_MAC_CFG1_SOFTRST);
	udelay(100);
	TSI_WRITE(TSI108_MAC_CFG1, 0);

	TSI_WRITE(TSI108_EC_PORTCTRL, TSI108_EC_PORTCTRL_STATRST);
	udelay(100);
	TSI_WRITE(TSI108_EC_PORTCTRL,
			     TSI_READ(TSI108_EC_PORTCTRL) &
			     ~TSI108_EC_PORTCTRL_STATRST);

	TSI_WRITE(TSI108_EC_TXCFG, TSI108_EC_TXCFG_RST);
	udelay(100);
	TSI_WRITE(TSI108_EC_TXCFG,
			     TSI_READ(TSI108_EC_TXCFG) &
			     ~TSI108_EC_TXCFG_RST);

	TSI_WRITE(TSI108_EC_RXCFG, TSI108_EC_RXCFG_RST);
	udelay(100);
	TSI_WRITE(TSI108_EC_RXCFG,
			     TSI_READ(TSI108_EC_RXCFG) &
			     ~TSI108_EC_RXCFG_RST);

	TSI_WRITE(TSI108_MAC_MII_MGMT_CFG,
			     TSI_READ(TSI108_MAC_MII_MGMT_CFG) |
			     TSI108_MAC_MII_MGMT_RST);
	udelay(100);
	TSI_WRITE(TSI108_MAC_MII_MGMT_CFG,
			     (TSI_READ(TSI108_MAC_MII_MGMT_CFG) &
			     ~(TSI108_MAC_MII_MGMT_RST |
			       TSI108_MAC_MII_MGMT_CLK)) | 0x07);
}
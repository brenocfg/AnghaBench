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
typedef  int u64 ;
struct niu {int flags; } ;

/* Variables and functions */
 int IPG_12_15_XGMII ; 
 int IPG_12_MII_GMII ; 
 int NIU_FLAGS_10G ; 
 int /*<<< orphan*/  TXMAC_BYTE_CNT ; 
 int /*<<< orphan*/  TXMAC_FRM_CNT ; 
 int /*<<< orphan*/  XMAC_CONFIG ; 
 int XMAC_CONFIG_ALWAYS_NO_CRC ; 
 int XMAC_CONFIG_STRETCH_MODE ; 
 int XMAC_CONFIG_TX_ENABLE ; 
 int XMAC_CONFIG_VAR_MIN_IPG_EN ; 
 int /*<<< orphan*/  XMAC_IPG ; 
 int XMAC_IPG_IPG_MII_GMII ; 
 int XMAC_IPG_IPG_MII_GMII_SHIFT ; 
 int XMAC_IPG_IPG_XGMII ; 
 int XMAC_IPG_IPG_XGMII_SHIFT ; 
 int /*<<< orphan*/  XMAC_MAX ; 
 int /*<<< orphan*/  XMAC_MIN ; 
 int XMAC_MIN_RX_MIN_PKT_SIZE ; 
 int XMAC_MIN_RX_MIN_PKT_SIZE_SHFT ; 
 int XMAC_MIN_TX_MIN_PKT_SIZE ; 
 int XMAC_MIN_TX_MIN_PKT_SIZE_SHFT ; 
 int /*<<< orphan*/  XTXMAC_STAT_MSK ; 
 int nr64_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64_mac (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void niu_init_tx_xmac(struct niu *np, u64 min, u64 max)
{
	u64 val;

	val = nr64_mac(XMAC_MIN);
	val &= ~(XMAC_MIN_TX_MIN_PKT_SIZE |
		 XMAC_MIN_RX_MIN_PKT_SIZE);
	val |= (min << XMAC_MIN_RX_MIN_PKT_SIZE_SHFT);
	val |= (min << XMAC_MIN_TX_MIN_PKT_SIZE_SHFT);
	nw64_mac(XMAC_MIN, val);

	nw64_mac(XMAC_MAX, max);

	nw64_mac(XTXMAC_STAT_MSK, ~(u64)0);

	val = nr64_mac(XMAC_IPG);
	if (np->flags & NIU_FLAGS_10G) {
		val &= ~XMAC_IPG_IPG_XGMII;
		val |= (IPG_12_15_XGMII << XMAC_IPG_IPG_XGMII_SHIFT);
	} else {
		val &= ~XMAC_IPG_IPG_MII_GMII;
		val |= (IPG_12_MII_GMII << XMAC_IPG_IPG_MII_GMII_SHIFT);
	}
	nw64_mac(XMAC_IPG, val);

	val = nr64_mac(XMAC_CONFIG);
	val &= ~(XMAC_CONFIG_ALWAYS_NO_CRC |
		 XMAC_CONFIG_STRETCH_MODE |
		 XMAC_CONFIG_VAR_MIN_IPG_EN |
		 XMAC_CONFIG_TX_ENABLE);
	nw64_mac(XMAC_CONFIG, val);

	nw64_mac(TXMAC_FRM_CNT, 0);
	nw64_mac(TXMAC_BYTE_CNT, 0);
}
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
typedef  int u32 ;
struct cmac {unsigned int offset; int /*<<< orphan*/  stats; struct adapter* adapter; } ;
struct addr_val_pair {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {scalar_t__ rev; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct addr_val_pair const*) ; 
 scalar_t__ A_XGM_RESET_CTRL ; 
 scalar_t__ A_XGM_RXFIFO_CFG ; 
#define  A_XGM_RX_CFG 147 
#define  A_XGM_RX_CTRL 146 
#define  A_XGM_RX_EXACT_MATCH_LOW_1 145 
#define  A_XGM_RX_EXACT_MATCH_LOW_2 144 
#define  A_XGM_RX_EXACT_MATCH_LOW_3 143 
#define  A_XGM_RX_EXACT_MATCH_LOW_4 142 
#define  A_XGM_RX_EXACT_MATCH_LOW_5 141 
#define  A_XGM_RX_EXACT_MATCH_LOW_6 140 
#define  A_XGM_RX_EXACT_MATCH_LOW_7 139 
#define  A_XGM_RX_EXACT_MATCH_LOW_8 138 
#define  A_XGM_RX_HASH_HIGH 137 
#define  A_XGM_RX_HASH_LOW 136 
 scalar_t__ A_XGM_RX_MAX_PKT_SIZE ; 
 scalar_t__ A_XGM_SERDES_CTRL ; 
 scalar_t__ A_XGM_SERDES_STATUS1 ; 
#define  A_XGM_STAT_CTRL 135 
 scalar_t__ A_XGM_TXFIFO_CFG ; 
#define  A_XGM_TX_CTRL 134 
 int /*<<< orphan*/  CH_ERR (struct adapter*,char*,int /*<<< orphan*/ ) ; 
#define  F_CLRSTATS 133 
 int /*<<< orphan*/  F_CMULOCK ; 
 int F_DISERRFRAMES ; 
#define  F_DISPAUSEFRAMES 132 
#define  F_EN1536BFRAMES 131 
#define  F_ENHASHMCAST 130 
#define  F_ENJUMBO 129 
 int F_MAC_RESET_ ; 
 int F_PCS_RESET_ ; 
 int F_RGMII_RESET_ ; 
#define  F_RMFCS 128 
 int F_RXENABLE ; 
 int F_RXENFRAMER ; 
 int F_RXSTRFRWRD ; 
 int F_SERDESRESET_ ; 
 int F_TXENABLE ; 
 int F_UNDERUNFIX ; 
 int F_XG2G_RESET_ ; 
 int F_XGMAC_STOP_EN ; 
 int /*<<< orphan*/  MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  M_RXMAXFRAMERSIZE ; 
 int V_RXMAXFRAMERSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ is_10G (struct adapter*) ; 
 int /*<<< orphan*/  macidx (struct cmac*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  t3_read_reg (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,scalar_t__,int,int) ; 
 scalar_t__ t3_wait_op_done (struct adapter*,scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,scalar_t__,int) ; 
 int /*<<< orphan*/  t3_write_regs (struct adapter*,struct addr_val_pair const*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  t3b_pcs_reset (struct cmac*) ; 
 scalar_t__ uses_xaui (struct adapter*) ; 
 int /*<<< orphan*/  xaui_serdes_reset (struct cmac*) ; 

int t3_mac_reset(struct cmac *mac)
{
	static const struct addr_val_pair mac_reset_avp[] = {
		{A_XGM_TX_CTRL, 0},
		{A_XGM_RX_CTRL, 0},
		{A_XGM_RX_CFG, F_DISPAUSEFRAMES | F_EN1536BFRAMES |
		 F_RMFCS | F_ENJUMBO | F_ENHASHMCAST},
		{A_XGM_RX_HASH_LOW, 0},
		{A_XGM_RX_HASH_HIGH, 0},
		{A_XGM_RX_EXACT_MATCH_LOW_1, 0},
		{A_XGM_RX_EXACT_MATCH_LOW_2, 0},
		{A_XGM_RX_EXACT_MATCH_LOW_3, 0},
		{A_XGM_RX_EXACT_MATCH_LOW_4, 0},
		{A_XGM_RX_EXACT_MATCH_LOW_5, 0},
		{A_XGM_RX_EXACT_MATCH_LOW_6, 0},
		{A_XGM_RX_EXACT_MATCH_LOW_7, 0},
		{A_XGM_RX_EXACT_MATCH_LOW_8, 0},
		{A_XGM_STAT_CTRL, F_CLRSTATS}
	};
	u32 val;
	struct adapter *adap = mac->adapter;
	unsigned int oft = mac->offset;

	t3_write_reg(adap, A_XGM_RESET_CTRL + oft, F_MAC_RESET_);
	t3_read_reg(adap, A_XGM_RESET_CTRL + oft);	/* flush */

	t3_write_regs(adap, mac_reset_avp, ARRAY_SIZE(mac_reset_avp), oft);
	t3_set_reg_field(adap, A_XGM_RXFIFO_CFG + oft,
			 F_RXSTRFRWRD | F_DISERRFRAMES,
			 uses_xaui(adap) ? 0 : F_RXSTRFRWRD);
	t3_set_reg_field(adap, A_XGM_TXFIFO_CFG + oft, 0, F_UNDERUNFIX);

	if (uses_xaui(adap)) {
		if (adap->params.rev == 0) {
			t3_set_reg_field(adap, A_XGM_SERDES_CTRL + oft, 0,
					 F_RXENABLE | F_TXENABLE);
			if (t3_wait_op_done(adap, A_XGM_SERDES_STATUS1 + oft,
					    F_CMULOCK, 1, 5, 2)) {
				CH_ERR(adap,
				       "MAC %d XAUI SERDES CMU lock failed\n",
				       macidx(mac));
				return -1;
			}
			t3_set_reg_field(adap, A_XGM_SERDES_CTRL + oft, 0,
					 F_SERDESRESET_);
		} else
			xaui_serdes_reset(mac);
	}

	t3_set_reg_field(adap, A_XGM_RX_MAX_PKT_SIZE + oft,
			 V_RXMAXFRAMERSIZE(M_RXMAXFRAMERSIZE),
			 V_RXMAXFRAMERSIZE(MAX_FRAME_SIZE) | F_RXENFRAMER);
	val = F_MAC_RESET_ | F_XGMAC_STOP_EN;

	if (is_10G(adap))
		val |= F_PCS_RESET_;
	else if (uses_xaui(adap))
		val |= F_PCS_RESET_ | F_XG2G_RESET_;
	else
		val |= F_RGMII_RESET_ | F_XG2G_RESET_;
	t3_write_reg(adap, A_XGM_RESET_CTRL + oft, val);
	t3_read_reg(adap, A_XGM_RESET_CTRL + oft);	/* flush */
	if ((val & F_PCS_RESET_) && adap->params.rev) {
		msleep(1);
		t3b_pcs_reset(mac);
	}

	memset(&mac->stats, 0, sizeof(mac->stats));
	return 0;
}
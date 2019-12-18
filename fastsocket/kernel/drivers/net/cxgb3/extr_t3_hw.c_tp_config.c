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
struct tp_params {int dummy; } ;
struct TYPE_2__ {scalar_t__ rev; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_DACK_CONFIG ; 
 int /*<<< orphan*/  A_TP_EGRESS_CONFIG ; 
 int /*<<< orphan*/  A_TP_GLOBAL_CONFIG ; 
 int /*<<< orphan*/  A_TP_IN_CONFIG ; 
 int /*<<< orphan*/  A_TP_MOD_CHANNEL_WEIGHT ; 
 int /*<<< orphan*/  A_TP_MOD_RATE_LIMIT ; 
 int /*<<< orphan*/  A_TP_PARA_REG3 ; 
 int /*<<< orphan*/  A_TP_PARA_REG4 ; 
 int /*<<< orphan*/  A_TP_PARA_REG6 ; 
 int /*<<< orphan*/  A_TP_PC_CONFIG ; 
 int /*<<< orphan*/  A_TP_PC_CONFIG2 ; 
 int /*<<< orphan*/  A_TP_PROXY_FLOW_CNTL ; 
 int /*<<< orphan*/  A_TP_TCP_OPTIONS ; 
 int /*<<< orphan*/  A_TP_TX_MOD_QUEUE_WEIGHT0 ; 
 int /*<<< orphan*/  A_TP_TX_MOD_QUEUE_WEIGHT1 ; 
 int /*<<< orphan*/  A_TP_TX_RESOURCE_LIMIT ; 
 int F_AUTOCAREFUL ; 
 int F_AUTOENABLE ; 
 int F_CHDRAFULL ; 
 int F_DISBLEDAPARBIT0 ; 
 int F_ENABLEARPMISS ; 
 int F_ENABLEEPCMDAFULL ; 
 int F_ENABLEESND ; 
 int F_ENABLEIPV6RSS ; 
 int F_ENABLENONOFDTNLSYN ; 
 int F_ENABLEOCSPIFULL ; 
 int F_HEARBEATDACK ; 
 int F_IPCHECKSUMOFFLOAD ; 
 int F_IPV6ENABLE ; 
 int F_LOCKTID ; 
 int F_MTUENABLE ; 
 int F_NICMODE ; 
 int F_PATHMTU ; 
 int /*<<< orphan*/  F_REWRITEFORCETOSIZE ; 
 int F_RXCONGESTIONMODE ; 
 int F_RXFBARBPRIO ; 
 int F_T3A_ENABLEESND ; 
 int F_TCPCHECKSUMOFFLOAD ; 
 int F_TXCONGESTIONMODE ; 
 int F_TXDEFERENABLE ; 
 int F_TXFBARBPRIO ; 
 int F_TXPACEAUTO ; 
 int F_TXPACEAUTOSTRICT ; 
 int F_TXPACEFIXED ; 
 int F_TXPACINGENABLE ; 
 int F_UDPCHECKSUMOFFLOAD ; 
 int M_TABLELATENCYDELTA ; 
 scalar_t__ T3_REV_C ; 
 int V_AUTOSTATE1 (int /*<<< orphan*/ ) ; 
 int V_AUTOSTATE2 (int) ; 
 int V_AUTOSTATE3 (int) ; 
 int V_BYTETHRESHOLD (int) ; 
 int V_DACK_MODE (int) ; 
 int V_IPTTL (int) ; 
 int V_MSSTHRESHOLD (int) ; 
 int V_MTUDEFAULT (int) ; 
 int V_SACKMODE (int) ; 
 int V_SACKRX (int) ; 
 int V_TABLELATENCYDELTA (int) ; 
 int V_TIMESTAMPSMODE (int) ; 
 int V_WINDOWSCALEMODE (int) ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tp_wr_indirect (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tp_config(struct adapter *adap, const struct tp_params *p)
{
	t3_write_reg(adap, A_TP_GLOBAL_CONFIG, F_TXPACINGENABLE | F_PATHMTU |
		     F_IPCHECKSUMOFFLOAD | F_UDPCHECKSUMOFFLOAD |
		     F_TCPCHECKSUMOFFLOAD | V_IPTTL(64));
	t3_write_reg(adap, A_TP_TCP_OPTIONS, V_MTUDEFAULT(576) |
		     F_MTUENABLE | V_WINDOWSCALEMODE(1) |
		     V_TIMESTAMPSMODE(1) | V_SACKMODE(1) | V_SACKRX(1));
	t3_write_reg(adap, A_TP_DACK_CONFIG, V_AUTOSTATE3(1) |
		     V_AUTOSTATE2(1) | V_AUTOSTATE1(0) |
		     V_BYTETHRESHOLD(26880) | V_MSSTHRESHOLD(2) |
		     F_AUTOCAREFUL | F_AUTOENABLE | V_DACK_MODE(1));
	t3_set_reg_field(adap, A_TP_IN_CONFIG, F_RXFBARBPRIO | F_TXFBARBPRIO,
			 F_IPV6ENABLE | F_NICMODE);
	t3_write_reg(adap, A_TP_TX_RESOURCE_LIMIT, 0x18141814);
	t3_write_reg(adap, A_TP_PARA_REG4, 0x5050105);
	t3_set_reg_field(adap, A_TP_PARA_REG6, 0,
			 adap->params.rev > 0 ? F_ENABLEESND :
			 F_T3A_ENABLEESND);

	t3_set_reg_field(adap, A_TP_PC_CONFIG,
			 F_ENABLEEPCMDAFULL,
			 F_ENABLEOCSPIFULL |F_TXDEFERENABLE | F_HEARBEATDACK |
			 F_TXCONGESTIONMODE | F_RXCONGESTIONMODE);
	t3_set_reg_field(adap, A_TP_PC_CONFIG2, F_CHDRAFULL,
			 F_ENABLEIPV6RSS | F_ENABLENONOFDTNLSYN |
			 F_ENABLEARPMISS | F_DISBLEDAPARBIT0);
	t3_write_reg(adap, A_TP_PROXY_FLOW_CNTL, 1080);
	t3_write_reg(adap, A_TP_PROXY_FLOW_CNTL, 1000);

	if (adap->params.rev > 0) {
		tp_wr_indirect(adap, A_TP_EGRESS_CONFIG, F_REWRITEFORCETOSIZE);
		t3_set_reg_field(adap, A_TP_PARA_REG3, F_TXPACEAUTO,
				 F_TXPACEAUTO);
		t3_set_reg_field(adap, A_TP_PC_CONFIG, F_LOCKTID, F_LOCKTID);
		t3_set_reg_field(adap, A_TP_PARA_REG3, 0, F_TXPACEAUTOSTRICT);
	} else
		t3_set_reg_field(adap, A_TP_PARA_REG3, 0, F_TXPACEFIXED);

	if (adap->params.rev == T3_REV_C)
		t3_set_reg_field(adap, A_TP_PC_CONFIG,
				 V_TABLELATENCYDELTA(M_TABLELATENCYDELTA),
				 V_TABLELATENCYDELTA(4));

	t3_write_reg(adap, A_TP_TX_MOD_QUEUE_WEIGHT1, 0);
	t3_write_reg(adap, A_TP_TX_MOD_QUEUE_WEIGHT0, 0);
	t3_write_reg(adap, A_TP_MOD_CHANNEL_WEIGHT, 0);
	t3_write_reg(adap, A_TP_MOD_RATE_LIMIT, 0xf2200000);
}
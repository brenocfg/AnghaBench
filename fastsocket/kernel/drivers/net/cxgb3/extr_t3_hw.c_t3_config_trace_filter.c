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
struct trace_params {int sport; int sip; int dport; int dip; int proto; int vlan; int intf; int sport_mask; int sip_mask; int dport_mask; int dip_mask; int proto_mask; int vlan_mask; int intf_mask; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_PIO_DATA ; 
 int A_TP_RX_TRC_KEY0 ; 
 int A_TP_TX_TRC_KEY0 ; 
 int /*<<< orphan*/  t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tp_wr_indirect (struct adapter*,int,int) ; 

void t3_config_trace_filter(struct adapter *adapter,
			    const struct trace_params *tp, int filter_index,
			    int invert, int enable)
{
	u32 addr, key[4], mask[4];

	key[0] = tp->sport | (tp->sip << 16);
	key[1] = (tp->sip >> 16) | (tp->dport << 16);
	key[2] = tp->dip;
	key[3] = tp->proto | (tp->vlan << 8) | (tp->intf << 20);

	mask[0] = tp->sport_mask | (tp->sip_mask << 16);
	mask[1] = (tp->sip_mask >> 16) | (tp->dport_mask << 16);
	mask[2] = tp->dip_mask;
	mask[3] = tp->proto_mask | (tp->vlan_mask << 8) | (tp->intf_mask << 20);

	if (invert)
		key[3] |= (1 << 29);
	if (enable)
		key[3] |= (1 << 28);

	addr = filter_index ? A_TP_RX_TRC_KEY0 : A_TP_TX_TRC_KEY0;
	tp_wr_indirect(adapter, addr++, key[0]);
	tp_wr_indirect(adapter, addr++, mask[0]);
	tp_wr_indirect(adapter, addr++, key[1]);
	tp_wr_indirect(adapter, addr++, mask[1]);
	tp_wr_indirect(adapter, addr++, key[2]);
	tp_wr_indirect(adapter, addr++, mask[2]);
	tp_wr_indirect(adapter, addr++, key[3]);
	tp_wr_indirect(adapter, addr, mask[3]);
	t3_read_reg(adapter, A_TP_PIO_DATA);
}
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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct rx_ring {int dummy; } ;
struct ql_adapter {int dummy; } ;
struct ib_mac_iocb_rsp {int flags2; int flags4; int flags3; int flags1; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  data_len; } ;

/* Variables and functions */
 int IB_MAC_CSUM_ERR_MASK ; 
 int IB_MAC_IOCB_RSP_DL ; 
 int IB_MAC_IOCB_RSP_DS ; 
 int IB_MAC_IOCB_RSP_HV ; 
 int IB_MAC_IOCB_RSP_T ; 
 int IB_MAC_IOCB_RSP_V ; 
 int IB_MAC_IOCB_RSP_VLAN_MASK ; 
 int /*<<< orphan*/  QL_DUMP_IB_MAC_RSP (struct ib_mac_iocb_rsp*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_process_mac_rx_gro_page (struct ql_adapter*,struct rx_ring*,struct ib_mac_iocb_rsp*,scalar_t__,int) ; 
 int /*<<< orphan*/  ql_process_mac_rx_page (struct ql_adapter*,struct rx_ring*,struct ib_mac_iocb_rsp*,scalar_t__,int) ; 
 int /*<<< orphan*/  ql_process_mac_rx_skb (struct ql_adapter*,struct rx_ring*,struct ib_mac_iocb_rsp*,scalar_t__,int) ; 
 int /*<<< orphan*/  ql_process_mac_split_rx_intr (struct ql_adapter*,struct rx_ring*,struct ib_mac_iocb_rsp*,int) ; 

__attribute__((used)) static unsigned long ql_process_mac_rx_intr(struct ql_adapter *qdev,
					struct rx_ring *rx_ring,
					struct ib_mac_iocb_rsp *ib_mac_rsp)
{
	u32 length = le32_to_cpu(ib_mac_rsp->data_len);
	u16 vlan_id = (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_V) ?
			((le16_to_cpu(ib_mac_rsp->vlan_id) &
			IB_MAC_IOCB_RSP_VLAN_MASK)) : 0xffff;

	QL_DUMP_IB_MAC_RSP(ib_mac_rsp);

	if (ib_mac_rsp->flags4 & IB_MAC_IOCB_RSP_HV) {
		/* The data and headers are split into
		 * separate buffers.
		 */
		ql_process_mac_split_rx_intr(qdev, rx_ring, ib_mac_rsp,
						vlan_id);
	} else if (ib_mac_rsp->flags3 & IB_MAC_IOCB_RSP_DS) {
		/* The data fit in a single small buffer.
		 * Allocate a new skb, copy the data and
		 * return the buffer to the free pool.
		 */
		ql_process_mac_rx_skb(qdev, rx_ring, ib_mac_rsp,
						length, vlan_id);
	} else if ((ib_mac_rsp->flags3 & IB_MAC_IOCB_RSP_DL) &&
		!(ib_mac_rsp->flags1 & IB_MAC_CSUM_ERR_MASK) &&
		(ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_T)) {
		/* TCP packet in a page chunk that's been checksummed.
		 * Tack it on to our GRO skb and let it go.
		 */
		ql_process_mac_rx_gro_page(qdev, rx_ring, ib_mac_rsp,
						length, vlan_id);
	} else if (ib_mac_rsp->flags3 & IB_MAC_IOCB_RSP_DL) {
		/* Non-TCP packet in a page chunk. Allocate an
		 * skb, tack it on frags, and send it up.
		 */
		ql_process_mac_rx_page(qdev, rx_ring, ib_mac_rsp,
						length, vlan_id);
	} else {
		/* Non-TCP/UDP large frames that span multiple buffers
		 * can be processed corrrectly by the split frame logic.
		 */
		ql_process_mac_split_rx_intr(qdev, rx_ring, ib_mac_rsp,
						vlan_id);
	}

	return (unsigned long)length;
}
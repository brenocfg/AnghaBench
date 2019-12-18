#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct ocrdma_grh {int /*<<< orphan*/ * dgid; void* pdid_hoplimit; void* tclass_flow; int /*<<< orphan*/ * sgid; int /*<<< orphan*/ * dmac; int /*<<< orphan*/ * smac; void* eth_type; void* vlan_tag; void* roce_eth_type; } ;
struct ocrdma_eth_vlan {int /*<<< orphan*/ * dgid; void* pdid_hoplimit; void* tclass_flow; int /*<<< orphan*/ * sgid; int /*<<< orphan*/ * dmac; int /*<<< orphan*/ * smac; void* eth_type; void* vlan_tag; void* roce_eth_type; } ;
struct ocrdma_eth_basic {int dummy; } ;
struct TYPE_6__ {struct ocrdma_grh* mac_addr; } ;
struct ocrdma_dev {int /*<<< orphan*/  ibdev; TYPE_1__ nic_info; } ;
struct ocrdma_ah {TYPE_3__* av; int /*<<< orphan*/  sgid_index; struct ocrdma_dev* dev; } ;
struct TYPE_9__ {struct ocrdma_grh* raw; } ;
struct TYPE_7__ {int traffic_class; int flow_label; int hop_limit; TYPE_4__ dgid; int /*<<< orphan*/  sgid_index; } ;
struct ib_ah_attr {int sl; TYPE_2__ grh; } ;
typedef  int /*<<< orphan*/  grh ;
typedef  int /*<<< orphan*/  eth ;
struct TYPE_8__ {int /*<<< orphan*/  valid; int /*<<< orphan*/  eth_hdr; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  OCRDMA_AV_VLAN_VALID ; 
 int OCRDMA_ROCE_ETH_TYPE ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ocrdma_grh*,int) ; 
 int /*<<< orphan*/  memset (struct ocrdma_grh*,int /*<<< orphan*/ ,int) ; 
 int ocrdma_query_gid (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,union ib_gid*) ; 
 int ocrdma_resolve_dgid (struct ocrdma_dev*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int rdma_get_vlan_id (TYPE_4__*) ; 

__attribute__((used)) static inline int set_av_attr(struct ocrdma_ah *ah,
				struct ib_ah_attr *attr, int pdid)
{
	int status = 0;
	u16 vlan_tag; bool vlan_enabled = false;
	struct ocrdma_dev *dev = ah->dev;
	struct ocrdma_eth_vlan eth;
	struct ocrdma_grh grh;
	int eth_sz;

	memset(&eth, 0, sizeof(eth));
	memset(&grh, 0, sizeof(grh));

	ah->sgid_index = attr->grh.sgid_index;

	vlan_tag = rdma_get_vlan_id(&attr->grh.dgid);
	if (vlan_tag && (vlan_tag < 0x1000)) {
		eth.eth_type = cpu_to_be16(0x8100);
		eth.roce_eth_type = cpu_to_be16(OCRDMA_ROCE_ETH_TYPE);
		vlan_tag |= (attr->sl & 7) << 13;
		eth.vlan_tag = cpu_to_be16(vlan_tag);
		eth_sz = sizeof(struct ocrdma_eth_vlan);
		vlan_enabled = true;
	} else {
		eth.eth_type = cpu_to_be16(OCRDMA_ROCE_ETH_TYPE);
		eth_sz = sizeof(struct ocrdma_eth_basic);
	}
	memcpy(&eth.smac[0], &dev->nic_info.mac_addr[0], ETH_ALEN);
	status = ocrdma_resolve_dgid(dev, &attr->grh.dgid, &eth.dmac[0]);
	if (status)
		return status;
	status = ocrdma_query_gid(&dev->ibdev, 1, attr->grh.sgid_index,
			(union ib_gid *)&grh.sgid[0]);
	if (status)
		return status;

	grh.tclass_flow = cpu_to_be32((6 << 28) |
			(attr->grh.traffic_class << 24) |
			attr->grh.flow_label);
	/* 0x1b is next header value in GRH */
	grh.pdid_hoplimit = cpu_to_be32((pdid << 16) |
			(0x1b << 8) | attr->grh.hop_limit);

	memcpy(&grh.dgid[0], attr->grh.dgid.raw, sizeof(attr->grh.dgid.raw));
	memcpy(&ah->av->eth_hdr, &eth, eth_sz);
	memcpy((u8 *)ah->av + eth_sz, &grh, sizeof(struct ocrdma_grh));
	if (vlan_enabled)
		ah->av->valid |= OCRDMA_AV_VLAN_VALID;
	return status;
}
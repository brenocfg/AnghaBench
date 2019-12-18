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
typedef  void* u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct ib_wc {int wc_flags; int /*<<< orphan*/  dlid_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  slid; } ;
struct ib_grh {int /*<<< orphan*/  version_tclass_flow; int /*<<< orphan*/  dgid; int /*<<< orphan*/  sgid; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {int flow_label; int hop_limit; int traffic_class; void* sgid_index; int /*<<< orphan*/  dgid; } ;
struct ib_ah_attr {TYPE_1__ grh; int /*<<< orphan*/  ah_flags; void* port_num; int /*<<< orphan*/  src_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  dlid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_AH_GRH ; 
 int IB_WC_GRH ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int ib_find_cached_gid (struct ib_device*,int /*<<< orphan*/ *,void**,scalar_t__*) ; 
 int /*<<< orphan*/  memset (struct ib_ah_attr*,int /*<<< orphan*/ ,int) ; 

int ib_init_ah_from_wc(struct ib_device *device, u8 port_num, struct ib_wc *wc,
		       struct ib_grh *grh, struct ib_ah_attr *ah_attr)
{
	u32 flow_class;
	u16 gid_index;
	int ret;

	memset(ah_attr, 0, sizeof *ah_attr);
	ah_attr->dlid = wc->slid;
	ah_attr->sl = wc->sl;
	ah_attr->src_path_bits = wc->dlid_path_bits;
	ah_attr->port_num = port_num;

	if (wc->wc_flags & IB_WC_GRH) {
		ah_attr->ah_flags = IB_AH_GRH;
		ah_attr->grh.dgid = grh->sgid;

		ret = ib_find_cached_gid(device, &grh->dgid, &port_num,
					 &gid_index);
		if (ret)
			return ret;

		ah_attr->grh.sgid_index = (u8) gid_index;
		flow_class = be32_to_cpu(grh->version_tclass_flow);
		ah_attr->grh.flow_label = flow_class & 0xFFFFF;
		ah_attr->grh.hop_limit = 0xFF;
		ah_attr->grh.traffic_class = (flow_class >> 20) & 0xFF;
	}
	return 0;
}
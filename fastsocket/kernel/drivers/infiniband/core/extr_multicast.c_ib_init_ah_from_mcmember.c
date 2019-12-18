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
typedef  scalar_t__ u16 ;
struct ib_sa_mcmember_rec {int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  mgid; int /*<<< orphan*/  rate; int /*<<< orphan*/  sl; int /*<<< orphan*/  mlid; int /*<<< orphan*/  port_gid; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; void* sgid_index; int /*<<< orphan*/  dgid; } ;
struct ib_ah_attr {TYPE_1__ grh; int /*<<< orphan*/  ah_flags; int /*<<< orphan*/  static_rate; void* port_num; int /*<<< orphan*/  sl; int /*<<< orphan*/  dlid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_AH_GRH ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int ib_find_cached_gid (struct ib_device*,int /*<<< orphan*/ *,void**,scalar_t__*) ; 
 int /*<<< orphan*/  memset (struct ib_ah_attr*,int /*<<< orphan*/ ,int) ; 

int ib_init_ah_from_mcmember(struct ib_device *device, u8 port_num,
			     struct ib_sa_mcmember_rec *rec,
			     struct ib_ah_attr *ah_attr)
{
	int ret;
	u16 gid_index;
	u8 p;

	ret = ib_find_cached_gid(device, &rec->port_gid, &p, &gid_index);
	if (ret)
		return ret;

	memset(ah_attr, 0, sizeof *ah_attr);
	ah_attr->dlid = be16_to_cpu(rec->mlid);
	ah_attr->sl = rec->sl;
	ah_attr->port_num = port_num;
	ah_attr->static_rate = rec->rate;

	ah_attr->ah_flags = IB_AH_GRH;
	ah_attr->grh.dgid = rec->mgid;

	ah_attr->grh.sgid_index = (u8) gid_index;
	ah_attr->grh.flow_label = be32_to_cpu(rec->flow_label);
	ah_attr->grh.hop_limit = rec->hop_limit;
	ah_attr->grh.traffic_class = rec->traffic_class;

	return 0;
}
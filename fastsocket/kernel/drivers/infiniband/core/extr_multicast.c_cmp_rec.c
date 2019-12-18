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
struct ib_sa_mcmember_rec {scalar_t__ qkey; scalar_t__ mlid; scalar_t__ traffic_class; scalar_t__ pkey; scalar_t__ sl; scalar_t__ flow_label; scalar_t__ hop_limit; scalar_t__ scope; int /*<<< orphan*/  packet_life_time; int /*<<< orphan*/  packet_life_time_selector; int /*<<< orphan*/  rate; int /*<<< orphan*/  rate_selector; int /*<<< orphan*/  mtu; int /*<<< orphan*/  mtu_selector; int /*<<< orphan*/  port_gid; } ;
typedef  int ib_sa_comp_mask ;

/* Variables and functions */
 int EINVAL ; 
 int IB_SA_MCMEMBER_REC_FLOW_LABEL ; 
 int IB_SA_MCMEMBER_REC_HOP_LIMIT ; 
 int IB_SA_MCMEMBER_REC_MLID ; 
 int /*<<< orphan*/  IB_SA_MCMEMBER_REC_MTU ; 
 int /*<<< orphan*/  IB_SA_MCMEMBER_REC_MTU_SELECTOR ; 
 int /*<<< orphan*/  IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME ; 
 int /*<<< orphan*/  IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME_SELECTOR ; 
 int IB_SA_MCMEMBER_REC_PKEY ; 
 int IB_SA_MCMEMBER_REC_PORT_GID ; 
 int IB_SA_MCMEMBER_REC_QKEY ; 
 int /*<<< orphan*/  IB_SA_MCMEMBER_REC_RATE ; 
 int /*<<< orphan*/  IB_SA_MCMEMBER_REC_RATE_SELECTOR ; 
 int IB_SA_MCMEMBER_REC_SCOPE ; 
 int IB_SA_MCMEMBER_REC_SL ; 
 int IB_SA_MCMEMBER_REC_TRAFFIC_CLASS ; 
 scalar_t__ check_selector (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cmp_rec(struct ib_sa_mcmember_rec *src,
		   struct ib_sa_mcmember_rec *dst, ib_sa_comp_mask comp_mask)
{
	/* MGID must already match */

	if (comp_mask & IB_SA_MCMEMBER_REC_PORT_GID &&
	    memcmp(&src->port_gid, &dst->port_gid, sizeof src->port_gid))
		return -EINVAL;
	if (comp_mask & IB_SA_MCMEMBER_REC_QKEY && src->qkey != dst->qkey)
		return -EINVAL;
	if (comp_mask & IB_SA_MCMEMBER_REC_MLID && src->mlid != dst->mlid)
		return -EINVAL;
	if (check_selector(comp_mask, IB_SA_MCMEMBER_REC_MTU_SELECTOR,
			   IB_SA_MCMEMBER_REC_MTU, dst->mtu_selector,
			   src->mtu, dst->mtu))
		return -EINVAL;
	if (comp_mask & IB_SA_MCMEMBER_REC_TRAFFIC_CLASS &&
	    src->traffic_class != dst->traffic_class)
		return -EINVAL;
	if (comp_mask & IB_SA_MCMEMBER_REC_PKEY && src->pkey != dst->pkey)
		return -EINVAL;
	if (check_selector(comp_mask, IB_SA_MCMEMBER_REC_RATE_SELECTOR,
			   IB_SA_MCMEMBER_REC_RATE, dst->rate_selector,
			   src->rate, dst->rate))
		return -EINVAL;
	if (check_selector(comp_mask,
			   IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME_SELECTOR,
			   IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME,
			   dst->packet_life_time_selector,
			   src->packet_life_time, dst->packet_life_time))
		return -EINVAL;
	if (comp_mask & IB_SA_MCMEMBER_REC_SL && src->sl != dst->sl)
		return -EINVAL;
	if (comp_mask & IB_SA_MCMEMBER_REC_FLOW_LABEL &&
	    src->flow_label != dst->flow_label)
		return -EINVAL;
	if (comp_mask & IB_SA_MCMEMBER_REC_HOP_LIMIT &&
	    src->hop_limit != dst->hop_limit)
		return -EINVAL;
	if (comp_mask & IB_SA_MCMEMBER_REC_SCOPE && src->scope != dst->scope)
		return -EINVAL;

	/* join_state checked separately, proxy_join ignored */

	return 0;
}
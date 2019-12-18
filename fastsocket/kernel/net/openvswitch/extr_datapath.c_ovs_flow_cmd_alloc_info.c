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
struct sw_flow_actions {int dummy; } ;
struct sw_flow {int /*<<< orphan*/  sf_acts; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_flow_cmd_msg_size (struct sw_flow_actions const*) ; 
 struct sw_flow_actions* ovsl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *ovs_flow_cmd_alloc_info(struct sw_flow *flow)
{
	const struct sw_flow_actions *sf_acts;

	sf_acts = ovsl_dereference(flow->sf_acts);

	return genlmsg_new(ovs_flow_cmd_msg_size(sf_acts), GFP_KERNEL);
}
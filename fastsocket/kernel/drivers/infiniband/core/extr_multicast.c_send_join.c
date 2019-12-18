#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mcast_port {int /*<<< orphan*/  port_num; TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  comp_mask; int /*<<< orphan*/  rec; } ;
struct mcast_member {TYPE_1__ multicast; } ;
struct mcast_group {int query_id; int /*<<< orphan*/  query; struct mcast_member* last_join; struct mcast_port* port; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_MGMT_METHOD_SET ; 
 int ib_sa_mcmember_rec_query (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mcast_group*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  join_handler ; 
 int /*<<< orphan*/  sa_client ; 

__attribute__((used)) static int send_join(struct mcast_group *group, struct mcast_member *member)
{
	struct mcast_port *port = group->port;
	int ret;

	group->last_join = member;
	ret = ib_sa_mcmember_rec_query(&sa_client, port->dev->device,
				       port->port_num, IB_MGMT_METHOD_SET,
				       &member->multicast.rec,
				       member->multicast.comp_mask,
				       3000, GFP_KERNEL, join_handler, group,
				       &group->query);
	if (ret >= 0) {
		group->query_id = ret;
		ret = 0;
	}
	return ret;
}
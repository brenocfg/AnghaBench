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
struct net_device {struct garp_port* garp_port; } ;
struct garp_port {struct garp_applicant** applicants; } ;
struct TYPE_2__ {int /*<<< orphan*/  group_address; } ;
struct garp_application {size_t type; TYPE_1__ proto; } ;
struct garp_applicant {int /*<<< orphan*/  join_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GARP_EVENT_TRANSMIT_PDU ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_mc_delete (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  garp_gid_event (struct garp_applicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  garp_pdu_queue (struct garp_applicant*) ; 
 int /*<<< orphan*/  garp_queue_xmit (struct garp_applicant*) ; 
 int /*<<< orphan*/  garp_release_port (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct garp_applicant*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct garp_applicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void garp_uninit_applicant(struct net_device *dev, struct garp_application *appl)
{
	struct garp_port *port = dev->garp_port;
	struct garp_applicant *app = port->applicants[appl->type];

	ASSERT_RTNL();

	rcu_assign_pointer(port->applicants[appl->type], NULL);
	synchronize_rcu();

	/* Delete timer and generate a final TRANSMIT_PDU event to flush out
	 * all pending messages before the applicant is gone. */
	del_timer_sync(&app->join_timer);
	garp_gid_event(app, GARP_EVENT_TRANSMIT_PDU);
	garp_pdu_queue(app);
	garp_queue_xmit(app);

	dev_mc_delete(dev, appl->proto.group_address, ETH_ALEN, 0);
	kfree(app);
	garp_release_port(dev);
}
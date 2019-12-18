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
struct fcoe_port {int /*<<< orphan*/  destroy_work; } ;
struct fcoe_ctlr {struct fc_lport* lp; } ;
struct fc_lport {int dummy; } ;
struct bnx2fc_interface {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2fc_interface_cleanup (struct bnx2fc_interface*) ; 
 int /*<<< orphan*/  bnx2fc_interface_put (struct bnx2fc_interface*) ; 
 int /*<<< orphan*/  bnx2fc_stop (struct bnx2fc_interface*) ; 
 struct fcoe_ctlr* bnx2fc_to_ctlr (struct bnx2fc_interface*) ; 
 int /*<<< orphan*/  bnx2fc_wq ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct fcoe_port* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __bnx2fc_destroy(struct bnx2fc_interface *interface)
{
	struct fcoe_ctlr *ctlr = bnx2fc_to_ctlr(interface);
	struct fc_lport *lport = ctlr->lp;
	struct fcoe_port *port = lport_priv(lport);

	bnx2fc_interface_cleanup(interface);
	bnx2fc_stop(interface);
	list_del(&interface->list);
	bnx2fc_interface_put(interface);
	queue_work(bnx2fc_wq, &port->destroy_work);
}
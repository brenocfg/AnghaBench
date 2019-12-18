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
struct be_async_event_link_state {int port_link_status; } ;
struct TYPE_2__ {int link_speed; } ;
struct be_adapter {int flags; TYPE_1__ phy; } ;

/* Variables and functions */
 int BE_FLAGS_LINK_STATUS_INIT ; 
 int LOGICAL_LINK_STATUS_MASK ; 
 int /*<<< orphan*/  be_link_status_update (struct be_adapter*,int) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 

__attribute__((used)) static void be_async_link_state_process(struct be_adapter *adapter,
		struct be_async_event_link_state *evt)
{
	/* When link status changes, link speed must be re-queried from FW */
	adapter->phy.link_speed = -1;

	/* Ignore physical link event */
	if (lancer_chip(adapter) &&
	    !(evt->port_link_status & LOGICAL_LINK_STATUS_MASK))
		return;

	/* For the initial link status do not rely on the ASYNC event as
	 * it may not be received in some cases.
	 */
	if (adapter->flags & BE_FLAGS_LINK_STATUS_INIT)
		be_link_status_update(adapter, evt->port_link_status);
}
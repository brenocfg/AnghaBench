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
struct sas_ha_struct {int dummy; } ;
struct asd_sas_phy {TYPE_1__* port_events; int /*<<< orphan*/  port_events_pending; struct sas_ha_struct* ha; } ;
typedef  enum port_event { ____Placeholder_port_event } port_event ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PORT_NUM_EVENTS ; 
 int /*<<< orphan*/  sas_queue_event (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sas_ha_struct*) ; 

__attribute__((used)) static void notify_port_event(struct asd_sas_phy *phy, enum port_event event)
{
	struct sas_ha_struct *ha = phy->ha;

	BUG_ON(event >= PORT_NUM_EVENTS);

	sas_queue_event(event, &phy->port_events_pending,
			&phy->port_events[event].work, ha);
}
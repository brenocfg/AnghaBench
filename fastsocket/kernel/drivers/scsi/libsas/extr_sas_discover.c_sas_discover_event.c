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
struct sas_discovery {TYPE_1__* disc_work; int /*<<< orphan*/  pending; } ;
struct asd_sas_port {int /*<<< orphan*/  ha; struct sas_discovery disc; } ;
typedef  enum discover_event { ____Placeholder_discover_event } discover_event ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DISC_NUM_EVENTS ; 
 int /*<<< orphan*/  sas_chain_event (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sas_discover_event(struct asd_sas_port *port, enum discover_event ev)
{
	struct sas_discovery *disc;

	if (!port)
		return 0;
	disc = &port->disc;

	BUG_ON(ev >= DISC_NUM_EVENTS);

	sas_chain_event(ev, &disc->pending, &disc->disc_work[ev].work, port->ha);

	return 0;
}
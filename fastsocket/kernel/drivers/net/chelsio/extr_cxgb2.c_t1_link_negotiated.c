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
struct port_info {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int nports; } ;
struct adapter {int /*<<< orphan*/  sge; TYPE_1__ params; struct port_info* port; } ;

/* Variables and functions */
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  link_report (struct port_info*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_sched_update_parms (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int) ; 

void t1_link_negotiated(struct adapter *adapter, int port_id, int link_stat,
			int speed, int duplex, int pause)
{
	struct port_info *p = &adapter->port[port_id];

	if (link_stat != netif_carrier_ok(p->dev)) {
		if (link_stat)
			netif_carrier_on(p->dev);
		else
			netif_carrier_off(p->dev);
		link_report(p);

		/* multi-ports: inform toe */
		if ((speed > 0) && (adapter->params.nports > 1)) {
			unsigned int sched_speed = 10;
			switch (speed) {
			case SPEED_1000:
				sched_speed = 1000;
				break;
			case SPEED_100:
				sched_speed = 100;
				break;
			case SPEED_10:
				sched_speed = 10;
				break;
			}
			t1_sched_update_parms(adapter->sge, port_id, 0, sched_speed);
		}
	}
}
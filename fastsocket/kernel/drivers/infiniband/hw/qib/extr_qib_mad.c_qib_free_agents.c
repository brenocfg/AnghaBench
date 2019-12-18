#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qib_ibport {TYPE_1__* sm_ah; struct ib_mad_agent* send_agent; } ;
struct qib_ibdev {int dummy; } ;
struct qib_devdata {int num_pports; TYPE_3__* pport; } ;
struct ib_mad_agent {int dummy; } ;
struct TYPE_8__ {scalar_t__ data; } ;
struct TYPE_6__ {TYPE_4__ timer; } ;
struct TYPE_7__ {TYPE_2__ cong_stats; struct qib_ibport ibport_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  ibah; } ;

/* Variables and functions */
 struct qib_devdata* dd_from_dev (struct qib_ibdev*) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_4__*) ; 
 int /*<<< orphan*/  ib_destroy_ah (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_mad_agent (struct ib_mad_agent*) ; 

void qib_free_agents(struct qib_ibdev *dev)
{
	struct qib_devdata *dd = dd_from_dev(dev);
	struct ib_mad_agent *agent;
	struct qib_ibport *ibp;
	int p;

	for (p = 0; p < dd->num_pports; p++) {
		ibp = &dd->pport[p].ibport_data;
		if (ibp->send_agent) {
			agent = ibp->send_agent;
			ibp->send_agent = NULL;
			ib_unregister_mad_agent(agent);
		}
		if (ibp->sm_ah) {
			ib_destroy_ah(&ibp->sm_ah->ibah);
			ibp->sm_ah = NULL;
		}
		if (dd->pport[p].cong_stats.timer.data)
			del_timer_sync(&dd->pport[p].cong_stats.timer);
	}
}
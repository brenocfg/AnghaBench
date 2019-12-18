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
struct work_struct {int dummy; } ;
struct sas_ha_struct {int /*<<< orphan*/  disco_mutex; int /*<<< orphan*/  state; } ;
struct sas_discovery_event {struct asd_sas_port* port; } ;
struct TYPE_2__ {int /*<<< orphan*/  pending; } ;
struct asd_sas_port {int /*<<< orphan*/  id; scalar_t__ port_dev; TYPE_1__ disc; struct sas_ha_struct* ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCE_REVALIDATE_DOMAIN ; 
 int /*<<< orphan*/  SAS_DPRINTK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  SAS_HA_ATA_EH_ACTIVE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sas_ex_revalidate_domain (scalar_t__) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sas_discovery_event* to_sas_discovery_event (struct work_struct*) ; 

__attribute__((used)) static void sas_revalidate_domain(struct work_struct *work)
{
	int res = 0;
	struct sas_discovery_event *ev = to_sas_discovery_event(work);
	struct asd_sas_port *port = ev->port;
	struct sas_ha_struct *ha = port->ha;

	/* prevent revalidation from finding sata links in recovery */
	mutex_lock(&ha->disco_mutex);
	if (test_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state)) {
		SAS_DPRINTK("REVALIDATION DEFERRED on port %d, pid:%d\n",
			    port->id, task_pid_nr(current));
		goto out;
	}

	clear_bit(DISCE_REVALIDATE_DOMAIN, &port->disc.pending);

	SAS_DPRINTK("REVALIDATING DOMAIN on port %d, pid:%d\n", port->id,
		    task_pid_nr(current));

	if (port->port_dev)
		res = sas_ex_revalidate_domain(port->port_dev);

	SAS_DPRINTK("done REVALIDATING DOMAIN on port %d, pid:%d, res 0x%x\n",
		    port->id, task_pid_nr(current), res);
 out:
	mutex_unlock(&ha->disco_mutex);
}
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
struct sas_ha_struct {int num_phys; int /*<<< orphan*/  disco_mutex; struct asd_sas_port** sas_port; int /*<<< orphan*/  state; } ;
struct sas_discovery {TYPE_1__* disc_work; int /*<<< orphan*/  pending; } ;
struct asd_sas_port {struct sas_discovery disc; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int DISCE_REVALIDATE_DOMAIN ; 
 int /*<<< orphan*/  SAS_HA_ATA_EH_ACTIVE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_queue_event (int const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sas_ha_struct*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int const,int /*<<< orphan*/ *) ; 

void sas_enable_revalidation(struct sas_ha_struct *ha)
{
	int i;

	mutex_lock(&ha->disco_mutex);
	clear_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state);
	for (i = 0; i < ha->num_phys; i++) {
		struct asd_sas_port *port = ha->sas_port[i];
		const int ev = DISCE_REVALIDATE_DOMAIN;
		struct sas_discovery *d = &port->disc;

		if (!test_and_clear_bit(ev, &d->pending))
			continue;

		sas_queue_event(ev, &d->pending, &d->disc_work[ev].work, ha);
	}
	mutex_unlock(&ha->disco_mutex);
}
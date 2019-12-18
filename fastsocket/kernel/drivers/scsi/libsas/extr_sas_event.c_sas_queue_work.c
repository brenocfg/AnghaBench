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
struct sas_work {int /*<<< orphan*/  work; int /*<<< orphan*/  drain_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  shost; } ;
struct sas_ha_struct {TYPE_1__ core; int /*<<< orphan*/  defer_q; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_HA_DRAINING ; 
 int /*<<< orphan*/  SAS_HA_REGISTERED ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void sas_queue_work(struct sas_ha_struct *ha, struct sas_work *sw)
{
	if (!test_bit(SAS_HA_REGISTERED, &ha->state))
		return;

	if (test_bit(SAS_HA_DRAINING, &ha->state)) {
		/* add it to the defer list, if not already pending */
		if (list_empty(&sw->drain_node))
			list_add(&sw->drain_node, &ha->defer_q);
	} else
		scsi_queue_work(ha->core.shost, &sw->work);
}
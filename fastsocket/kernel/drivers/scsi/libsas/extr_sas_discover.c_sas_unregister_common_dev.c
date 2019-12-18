#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sas_ha_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  eh_active; } ;
struct TYPE_6__ {int /*<<< orphan*/  eh_list_node; } ;
struct TYPE_5__ {int /*<<< orphan*/  ap; } ;
struct domain_device {scalar_t__ dev_type; TYPE_3__ ssp_dev; TYPE_2__ sata_dev; int /*<<< orphan*/  dev_list_node; int /*<<< orphan*/  siblings; TYPE_1__* port; int /*<<< orphan*/  parent; } ;
struct asd_sas_port {int /*<<< orphan*/  dev_list_lock; struct sas_ha_struct* ha; } ;
struct TYPE_4__ {int /*<<< orphan*/ * port_dev; } ;

/* Variables and functions */
 scalar_t__ SAS_END_DEV ; 
 scalar_t__ dev_is_sata (struct domain_device*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_ata_end_eh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_notify_lldd_dev_gone (struct domain_device*) ; 
 int /*<<< orphan*/  sas_put_device (struct domain_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sas_unregister_common_dev(struct asd_sas_port *port, struct domain_device *dev)
{
	struct sas_ha_struct *ha = port->ha;

	sas_notify_lldd_dev_gone(dev);
	if (!dev->parent)
		dev->port->port_dev = NULL;
	else
		list_del_init(&dev->siblings);

	spin_lock_irq(&port->dev_list_lock);
	list_del_init(&dev->dev_list_node);
	if (dev_is_sata(dev))
		sas_ata_end_eh(dev->sata_dev.ap);
	spin_unlock_irq(&port->dev_list_lock);

	spin_lock_irq(&ha->lock);
	if (dev->dev_type == SAS_END_DEV &&
	    !list_empty(&dev->ssp_dev.eh_list_node)) {
		list_del_init(&dev->ssp_dev.eh_list_node);
		ha->eh_active--;
	}
	spin_unlock_irq(&ha->lock);

	sas_put_device(dev);
}
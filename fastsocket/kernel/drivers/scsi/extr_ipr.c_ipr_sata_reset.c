#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipr_sata_port {struct ipr_resource_entry* res; struct ipr_ioa_cfg* ioa_cfg; } ;
struct ipr_resource_entry {unsigned int ata_class; } ;
struct ipr_ioa_cfg {TYPE_2__* host; scalar_t__ in_reset_reload; int /*<<< orphan*/  reset_wait_q; } ;
struct ata_link {TYPE_1__* ap; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_3__ {struct ipr_sata_port* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int ENXIO ; 
 int /*<<< orphan*/  LEAVE ; 
 int ipr_device_reset (struct ipr_ioa_cfg*,struct ipr_resource_entry*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipr_sata_reset(struct ata_link *link, unsigned int *classes,
				unsigned long deadline)
{
	struct ipr_sata_port *sata_port = link->ap->private_data;
	struct ipr_ioa_cfg *ioa_cfg = sata_port->ioa_cfg;
	struct ipr_resource_entry *res;
	unsigned long lock_flags = 0;
	int rc = -ENXIO;

	ENTER;
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	while(ioa_cfg->in_reset_reload) {
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		wait_event(ioa_cfg->reset_wait_q, !ioa_cfg->in_reset_reload);
		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	}

	res = sata_port->res;
	if (res) {
		rc = ipr_device_reset(ioa_cfg, res);
		*classes = res->ata_class;
	}

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	LEAVE;
	return rc;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * scsi_cmd; } ;
typedef  TYPE_1__ ips_scb_t ;
struct TYPE_8__ {int /*<<< orphan*/  pcidev; } ;
typedef  TYPE_2__ ips_ha_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_PRINTK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  ips_done (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void
ipsintr_done(ips_ha_t * ha, ips_scb_t * scb)
{
	METHOD_TRACE("ipsintr_done", 2);

	if (!scb) {
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "Spurious interrupt; scb NULL.\n");

		return;
	}

	if (scb->scsi_cmd == NULL) {
		/* unexpected interrupt */
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "Spurious interrupt; scsi_cmd not set.\n");

		return;
	}

	ips_done(ha, scb);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int present; int /*<<< orphan*/  port_flags; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_PFLAG_PROBING ; 
 int /*<<< orphan*/  hwif_register_devices (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_acpi_port_init_devices (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_port_apply_params (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_port_cable_detect (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_port_init_devices (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_port_setup_devices (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_port_tune_devices (TYPE_1__*) ; 
 int ide_probe_port (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_proc_port_register_devices (TYPE_1__*) ; 

void ide_port_scan(ide_hwif_t *hwif)
{
	int rc;

	ide_port_apply_params(hwif);
	ide_port_cable_detect(hwif);

	hwif->port_flags |= IDE_PFLAG_PROBING;

	ide_port_init_devices(hwif);

	rc = ide_probe_port(hwif);

	hwif->port_flags &= ~IDE_PFLAG_PROBING;

	if (rc < 0)
		return;

	hwif->present = 1;

	ide_port_tune_devices(hwif);
	ide_port_setup_devices(hwif);
	ide_acpi_port_init_devices(hwif);
	hwif_register_devices(hwif);
	ide_proc_port_register_devices(hwif);
}
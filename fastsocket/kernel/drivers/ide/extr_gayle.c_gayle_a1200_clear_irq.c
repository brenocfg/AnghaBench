#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  irq_addr; int /*<<< orphan*/  status_addr; } ;
struct TYPE_6__ {TYPE_1__ io_ports; } ;
typedef  TYPE_2__ ide_hwif_t ;
struct TYPE_7__ {TYPE_2__* hwif; } ;
typedef  TYPE_3__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  z_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  z_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gayle_a1200_clear_irq(ide_drive_t *drive)
{
    ide_hwif_t *hwif = drive->hwif;

    (void)z_readb(hwif->io_ports.status_addr);
    z_writeb(0x7c, hwif->io_ports.irq_addr);
}
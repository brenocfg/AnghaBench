#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ata_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfin_check_status (struct ata_port*) ; 
 int /*<<< orphan*/  bfin_irq_on (struct ata_port*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

void bfin_thaw(struct ata_port *ap)
{
	dev_dbg(ap->dev, "in atapi dma thaw\n");
	bfin_check_status(ap);
	bfin_irq_on(ap);
}
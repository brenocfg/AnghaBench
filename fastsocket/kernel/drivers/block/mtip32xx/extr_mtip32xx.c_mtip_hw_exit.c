#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct driver_data {TYPE_2__* port; TYPE_1__* pdev; int /*<<< orphan*/  tasklet; scalar_t__ mmio; int /*<<< orphan*/  dd_flag; } ;
struct TYPE_6__ {int /*<<< orphan*/  command_list_dma; int /*<<< orphan*/  command_list; int /*<<< orphan*/  cmd_timer; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ATA_SECT_SIZE ; 
 scalar_t__ HOST_CTL ; 
 int HOST_IRQ_EN ; 
 scalar_t__ HW_PORT_PRIV_DMA_SZ ; 
 int /*<<< orphan*/  MTIP_DDF_CLEANUP_BIT ; 
 int /*<<< orphan*/  MTIP_PF_REBUILD_BIT ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct driver_data*) ; 
 int /*<<< orphan*/  dmam_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  mtip_deinit_port (TYPE_2__*) ; 
 scalar_t__ mtip_standby_immediate (TYPE_2__*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtip_hw_exit(struct driver_data *dd)
{
	/*
	 * Send standby immediate (E0h) to the drive so that it
	 * saves its state.
	 */
	if (!test_bit(MTIP_DDF_CLEANUP_BIT, &dd->dd_flag)) {

		if (!test_bit(MTIP_PF_REBUILD_BIT, &dd->port->flags))
			if (mtip_standby_immediate(dd->port))
				dev_warn(&dd->pdev->dev,
					"STANDBY IMMEDIATE failed\n");

		/* de-initialize the port. */
		mtip_deinit_port(dd->port);

		/* Disable interrupts on the HBA. */
		writel(readl(dd->mmio + HOST_CTL) & ~HOST_IRQ_EN,
				dd->mmio + HOST_CTL);
	}

	del_timer_sync(&dd->port->cmd_timer);

	/* Release the IRQ. */
	devm_free_irq(&dd->pdev->dev, dd->pdev->irq, dd);

	/* Stop the bottom half tasklet. */
	tasklet_kill(&dd->tasklet);

	/* Free the command/command header memory. */
	dmam_free_coherent(&dd->pdev->dev,
			HW_PORT_PRIV_DMA_SZ + (ATA_SECT_SIZE * 4),
			dd->port->command_list,
			dd->port->command_list_dma);
	/* Free the memory allocated for the for structure. */
	kfree(dd->port);

	return 0;
}
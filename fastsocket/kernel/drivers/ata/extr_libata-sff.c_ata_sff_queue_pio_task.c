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
struct ata_port {int /*<<< orphan*/  sff_pio_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_sff_wq ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ata_sff_queue_pio_task(struct ata_port *ap, unsigned long delay)
{
	/* may fail if ata_sff_flush_pio_task() in progress */
	queue_delayed_work(ata_sff_wq, &ap->sff_pio_task,
			   msecs_to_jiffies(delay));
}
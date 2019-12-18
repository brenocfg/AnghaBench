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
struct spi_message {int status; int /*<<< orphan*/  context; int /*<<< orphan*/  (* complete ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  actual_length; int /*<<< orphan*/  queue; int /*<<< orphan*/  spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct spi_master {TYPE_1__ dev; } ;
struct atmel_spi {scalar_t__ stopping; int /*<<< orphan*/  queue; int /*<<< orphan*/ * next_transfer; int /*<<< orphan*/ * current_transfer; int /*<<< orphan*/  lock; int /*<<< orphan*/  stay; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTCR ; 
 int /*<<< orphan*/  RXTDIS ; 
 int SPI_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXTDIS ; 
 int /*<<< orphan*/  atmel_spi_next_message (struct spi_master*) ; 
 int /*<<< orphan*/  cs_deactivate (struct atmel_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_writel (struct atmel_spi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atmel_spi_msg_done(struct spi_master *master, struct atmel_spi *as,
		struct spi_message *msg, int status, int stay)
{
	if (!stay || status < 0)
		cs_deactivate(as, msg->spi);
	else
		as->stay = msg->spi;

	list_del(&msg->queue);
	msg->status = status;

	dev_dbg(master->dev.parent,
		"xfer complete: %u bytes transferred\n",
		msg->actual_length);

	spin_unlock(&as->lock);
	msg->complete(msg->context);
	spin_lock(&as->lock);

	as->current_transfer = NULL;
	as->next_transfer = NULL;

	/* continue if needed */
	if (list_empty(&as->queue) || as->stopping)
		spi_writel(as, PTCR, SPI_BIT(RXTDIS) | SPI_BIT(TXTDIS));
	else
		atmel_spi_next_message(master);
}
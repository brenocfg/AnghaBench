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
struct nand_chip {TYPE_1__* controller; } ;
struct tmio_nand {TYPE_2__* dev; scalar_t__ fcr; struct nand_chip chip; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 scalar_t__ FCR_IMR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tmio_iowrite8 (int,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t tmio_irq(int irq, void *__tmio)
{
	struct tmio_nand *tmio = __tmio;
	struct nand_chip *nand_chip = &tmio->chip;

	/* disable RDYREQ interrupt */
	tmio_iowrite8(0x00, tmio->fcr + FCR_IMR);

	if (unlikely(!waitqueue_active(&nand_chip->controller->wq)))
		dev_warn(&tmio->dev->dev, "spurious interrupt\n");

	wake_up(&nand_chip->controller->wq);
	return IRQ_HANDLED;
}
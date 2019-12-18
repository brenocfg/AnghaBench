#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * dpram; scalar_t__ iobase; int /*<<< orphan*/  irq; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */
 scalar_t__ PCI9050_INTR_REG ; 
 scalar_t__ PCI9050_USER_IO ; 
 int /*<<< orphan*/  ergo_stopcard (TYPE_1__*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 

__attribute__((used)) static void
ergo_releasehardware(hysdn_card * card)
{
	ergo_stopcard(card);	/* first stop the card if not already done */
	free_irq(card->irq, card);	/* release interrupt */
	release_region(card->iobase + PCI9050_INTR_REG, 1);	/* release all io ports */
	release_region(card->iobase + PCI9050_USER_IO, 1);
	iounmap(card->dpram);
	card->dpram = NULL;	/* release shared mem */
}
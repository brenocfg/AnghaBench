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
struct TYPE_4__ {int /*<<< orphan*/  IntType; scalar_t__ Attributes; } ;
struct TYPE_3__ {int /*<<< orphan*/  Handler; int /*<<< orphan*/  Attributes; } ;
struct pcmcia_device {TYPE_2__ conf; TYPE_1__ irq; struct orinoco_private* priv; int /*<<< orphan*/  dev; } ;
struct orinoco_private {struct orinoco_pccard* card; } ;
struct orinoco_pccard {struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  IRQ_TYPE_DYNAMIC_SHARING ; 
 struct orinoco_private* alloc_orinocodev (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  orinoco_interrupt ; 
 int spectrum_cs_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  spectrum_cs_hard_reset ; 
 int /*<<< orphan*/  spectrum_cs_stop_firmware ; 

__attribute__((used)) static int
spectrum_cs_probe(struct pcmcia_device *link)
{
	struct orinoco_private *priv;
	struct orinoco_pccard *card;

	priv = alloc_orinocodev(sizeof(*card), &link->dev,
				spectrum_cs_hard_reset,
				spectrum_cs_stop_firmware);
	if (!priv)
		return -ENOMEM;
	card = priv->card;

	/* Link both structures together */
	card->p_dev = link;
	link->priv = priv;

#if 1 /* in RHEL */
	/* Interrupt setup */
	link->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING;
	link->irq.Handler = orinoco_interrupt;
	link->conf.Attributes = 0;
	link->conf.IntType = INT_MEMORY_AND_IO;
#endif

	return spectrum_cs_config(link);
}
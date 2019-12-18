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
struct TYPE_5__ {int /*<<< orphan*/  IntType; scalar_t__ Attributes; } ;
struct TYPE_6__ {int IRQInfo1; int /*<<< orphan*/ * Handler; int /*<<< orphan*/  Attributes; } ;
struct pcmcia_device {TYPE_1__ conf; TYPE_2__ irq; TYPE_3__* priv; } ;
struct TYPE_7__ {struct pcmcia_device* p_dev; } ;
typedef  TYPE_3__ local_info_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int IRQ_INFO2_VALID ; 
 int IRQ_LEVEL_ID ; 
 int /*<<< orphan*/  IRQ_TYPE_EXCLUSIVE ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int sl811_cs_config (struct pcmcia_device*) ; 

__attribute__((used)) static int sl811_cs_probe(struct pcmcia_device *link)
{
	local_info_t *local;

	local = kzalloc(sizeof(local_info_t), GFP_KERNEL);
	if (!local)
		return -ENOMEM;
	local->p_dev = link;
	link->priv = local;

	/* Initialize */
	link->irq.Attributes = IRQ_TYPE_EXCLUSIVE;
	link->irq.IRQInfo1 = IRQ_INFO2_VALID|IRQ_LEVEL_ID;
	link->irq.Handler = NULL;

	link->conf.Attributes = 0;
	link->conf.IntType = INT_MEMORY_AND_IO;

	return sl811_cs_config(link);
}
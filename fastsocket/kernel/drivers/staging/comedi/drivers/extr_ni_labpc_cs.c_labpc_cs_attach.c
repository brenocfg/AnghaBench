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
struct TYPE_3__ {int Attributes; int IRQInfo1; int /*<<< orphan*/ * Handler; } ;
struct pcmcia_device {TYPE_2__ conf; TYPE_1__ irq; struct local_info_t* priv; } ;
struct local_info_t {struct pcmcia_device* link; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int IRQ_FORCED_PULSE ; 
 int IRQ_INFO2_VALID ; 
 int IRQ_PULSE_ID ; 
 int IRQ_TYPE_DYNAMIC_SHARING ; 
 struct local_info_t* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  labpc_config (struct pcmcia_device*) ; 
 struct pcmcia_device* pcmcia_cur_dev ; 

__attribute__((used)) static int labpc_cs_attach(struct pcmcia_device *link)
{
	struct local_info_t *local;

	DEBUG(0, "labpc_cs_attach()\n");

	/* Allocate space for private device-specific data */
	local = kzalloc(sizeof(struct local_info_t), GFP_KERNEL);
	if (!local)
		return -ENOMEM;
	local->link = link;
	link->priv = local;

	/* Interrupt setup */
	link->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING | IRQ_FORCED_PULSE;
	link->irq.IRQInfo1 = IRQ_INFO2_VALID | IRQ_PULSE_ID;
	link->irq.Handler = NULL;

	/*
	   General socket configuration defaults can go here.  In this
	   client, we assume very little, and rely on the CIS for almost
	   everything.  In most clients, many details (i.e., number, sizes,
	   and attributes of IO windows) are fixed by the nature of the
	   device, and can be hard-wired here.
	 */
	link->conf.Attributes = 0;
	link->conf.IntType = INT_MEMORY_AND_IO;

	pcmcia_cur_dev = link;

	labpc_config(link);

	return 0;
}
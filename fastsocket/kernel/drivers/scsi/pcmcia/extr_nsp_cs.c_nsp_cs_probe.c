#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  IntType; int /*<<< orphan*/  Attributes; } ;
struct TYPE_7__ {int Attributes; struct pcmcia_device* Instance; int /*<<< orphan*/ * Handler; int /*<<< orphan*/  IRQInfo1; } ;
struct TYPE_6__ {int NumPorts1; int IOAddrLines; int /*<<< orphan*/  Attributes1; } ;
struct pcmcia_device {TYPE_3__ conf; TYPE_2__ irq; TYPE_1__ io; struct pcmcia_device* priv; struct pcmcia_device* p_dev; } ;
typedef  struct pcmcia_device scsi_info_t ;
struct TYPE_9__ {struct pcmcia_device* ScsiInfo; } ;
typedef  TYPE_4__ nsp_hw_data ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_AUTO ; 
 int IRQF_SHARED ; 
 int IRQ_HANDLE_PRESENT ; 
 int /*<<< orphan*/  IRQ_LEVEL_ID ; 
 int IRQ_TYPE_EXCLUSIVE ; 
 int /*<<< orphan*/  NSP_DEBUG_INIT ; 
 struct pcmcia_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nsp_cs_config (struct pcmcia_device*) ; 
 TYPE_4__ nsp_data_base ; 
 int /*<<< orphan*/  nsp_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nspintr ; 

__attribute__((used)) static int nsp_cs_probe(struct pcmcia_device *link)
{
	scsi_info_t  *info;
	nsp_hw_data  *data = &nsp_data_base;
	int ret;

	nsp_dbg(NSP_DEBUG_INIT, "in");

	/* Create new SCSI device */
	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (info == NULL) { return -ENOMEM; }
	info->p_dev = link;
	link->priv = info;
	data->ScsiInfo = info;

	nsp_dbg(NSP_DEBUG_INIT, "info=0x%p", info);

	/* The io structure describes IO port mapping */
	link->io.NumPorts1	 = 0x10;
	link->io.Attributes1	 = IO_DATA_PATH_WIDTH_AUTO;
	link->io.IOAddrLines	 = 10;	/* not used */

	/* Interrupt setup */
	link->irq.Attributes	 = IRQ_TYPE_EXCLUSIVE | IRQ_HANDLE_PRESENT;
	link->irq.IRQInfo1	 = IRQ_LEVEL_ID;

	/* Interrupt handler */
	link->irq.Handler	 = &nspintr;
	link->irq.Instance       = info;
	link->irq.Attributes     |= IRQF_SHARED;

	/* General socket configuration */
	link->conf.Attributes	 = CONF_ENABLE_IRQ;
	link->conf.IntType	 = INT_MEMORY_AND_IO;

	ret = nsp_cs_config(link);

	nsp_dbg(NSP_DEBUG_INIT, "link=0x%p", link);
	return ret;
}
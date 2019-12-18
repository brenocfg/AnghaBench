#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  IntType; int /*<<< orphan*/  Attributes; } ;
struct TYPE_5__ {int /*<<< orphan*/  IRQInfo1; int /*<<< orphan*/  Attributes; } ;
struct TYPE_4__ {int NumPorts1; int /*<<< orphan*/  Attributes1; } ;
struct pcmcia_device {TYPE_3__ conf; TYPE_2__ irq; TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_16 ; 
 int /*<<< orphan*/  IRQ_LEVEL_ID ; 
 int /*<<< orphan*/  IRQ_TYPE_DYNAMIC_SHARING ; 
 struct pcmcia_device* cur_dev ; 
 int /*<<< orphan*/  mio_cs_config (struct pcmcia_device*) ; 

__attribute__((used)) static int cs_attach(struct pcmcia_device *link)
{
	link->io.Attributes1 = IO_DATA_PATH_WIDTH_16;
	link->io.NumPorts1 = 16;
	link->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING;
	link->irq.IRQInfo1 = IRQ_LEVEL_ID;
	link->conf.Attributes = CONF_ENABLE_IRQ;
	link->conf.IntType = INT_MEMORY_AND_IO;

	cur_dev = link;

	mio_cs_config(link);

	return 0;
}
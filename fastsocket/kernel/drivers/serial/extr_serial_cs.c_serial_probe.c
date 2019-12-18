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
struct serial_info {struct pcmcia_device* p_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  IntType; int /*<<< orphan*/  Status; int /*<<< orphan*/  Attributes; } ;
struct TYPE_5__ {int /*<<< orphan*/  IRQInfo1; int /*<<< orphan*/  Attributes; } ;
struct TYPE_4__ {int NumPorts1; int /*<<< orphan*/  Attributes1; } ;
struct pcmcia_device {TYPE_3__ conf; TYPE_2__ irq; TYPE_1__ io; struct serial_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCSR_AUDIO_ENA ; 
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  CONF_ENABLE_SPKR ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 int /*<<< orphan*/  IRQ_LEVEL_ID ; 
 int /*<<< orphan*/  IRQ_TYPE_DYNAMIC_SHARING ; 
 scalar_t__ do_sound ; 
 struct serial_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int serial_config (struct pcmcia_device*) ; 

__attribute__((used)) static int serial_probe(struct pcmcia_device *link)
{
	struct serial_info *info;

	DEBUG(0, "serial_attach()\n");

	/* Create new serial device */
	info = kzalloc(sizeof (*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;
	info->p_dev = link;
	link->priv = info;

	link->io.Attributes1 = IO_DATA_PATH_WIDTH_8;
	link->io.NumPorts1 = 8;
	link->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING;
	link->irq.IRQInfo1 = IRQ_LEVEL_ID;
	link->conf.Attributes = CONF_ENABLE_IRQ;
	if (do_sound) {
		link->conf.Attributes |= CONF_ENABLE_SPKR;
		link->conf.Status = CCSR_AUDIO_ENA;
	}
	link->conf.IntType = INT_MEMORY_AND_IO;

	return serial_config(link);
}
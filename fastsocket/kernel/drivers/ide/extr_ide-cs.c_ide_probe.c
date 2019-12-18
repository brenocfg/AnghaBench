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
struct TYPE_7__ {int /*<<< orphan*/  IRQInfo1; int /*<<< orphan*/  Attributes; } ;
struct TYPE_6__ {int IOAddrLines; int /*<<< orphan*/  Attributes2; int /*<<< orphan*/  Attributes1; } ;
struct pcmcia_device {TYPE_3__ conf; TYPE_2__ irq; TYPE_1__ io; TYPE_4__* priv; } ;
struct TYPE_9__ {struct pcmcia_device* p_dev; } ;
typedef  TYPE_4__ ide_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_AUTO ; 
 int /*<<< orphan*/  IRQ_LEVEL_ID ; 
 int /*<<< orphan*/  IRQ_TYPE_DYNAMIC_SHARING ; 
 int ide_config (struct pcmcia_device*) ; 
 TYPE_4__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ide_probe(struct pcmcia_device *link)
{
    ide_info_t *info;

    DEBUG(0, "ide_attach()\n");

    /* Create new ide device */
    info = kzalloc(sizeof(*info), GFP_KERNEL);
    if (!info)
	return -ENOMEM;

    info->p_dev = link;
    link->priv = info;

    link->io.Attributes1 = IO_DATA_PATH_WIDTH_AUTO;
    link->io.Attributes2 = IO_DATA_PATH_WIDTH_8;
    link->io.IOAddrLines = 3;
    link->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING;
    link->irq.IRQInfo1 = IRQ_LEVEL_ID;
    link->conf.Attributes = CONF_ENABLE_IRQ;
    link->conf.IntType = INT_MEMORY_AND_IO;

    return ide_config(link);
}
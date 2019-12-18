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
struct TYPE_7__ {int NumPorts1; int IOAddrLines; int /*<<< orphan*/  Attributes1; } ;
struct TYPE_6__ {int Attributes; int IRQInfo1; int /*<<< orphan*/ * Handler; } ;
struct pcmcia_device {TYPE_3__ conf; TYPE_2__ io; TYPE_1__ irq; TYPE_4__* priv; } ;
struct TYPE_9__ {int cardnr; struct pcmcia_device* p_dev; } ;
typedef  TYPE_4__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_AUTO ; 
 int IRQ_FIRST_SHARED ; 
 int IRQ_LEVEL_ID ; 
 int IRQ_SHARE_ID ; 
 int IRQ_TYPE_DYNAMIC_SHARING ; 
 TYPE_4__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int teles_cs_config (struct pcmcia_device*) ; 

__attribute__((used)) static int teles_probe(struct pcmcia_device *link)
{
    local_info_t *local;

    DEBUG(0, "teles_attach()\n");

    /* Allocate space for private device-specific data */
    local = kzalloc(sizeof(local_info_t), GFP_KERNEL);
    if (!local) return -ENOMEM;
    local->cardnr = -1;

    local->p_dev = link;
    link->priv = local;

    /* Interrupt setup */
    link->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING|IRQ_FIRST_SHARED;
    link->irq.IRQInfo1 = IRQ_LEVEL_ID|IRQ_SHARE_ID;
    link->irq.Handler = NULL;

    /*
      General socket configuration defaults can go here.  In this
      client, we assume very little, and rely on the CIS for almost
      everything.  In most clients, many details (i.e., number, sizes,
      and attributes of IO windows) are fixed by the nature of the
      device, and can be hard-wired here.
    */
    link->io.NumPorts1 = 96;
    link->io.Attributes1 = IO_DATA_PATH_WIDTH_AUTO;
    link->io.IOAddrLines = 5;

    link->conf.Attributes = CONF_ENABLE_IRQ;
    link->conf.IntType = INT_MEMORY_AND_IO;

    return teles_cs_config(link);
}
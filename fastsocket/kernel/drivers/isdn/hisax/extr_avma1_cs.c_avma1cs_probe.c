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
struct TYPE_6__ {int ConfigIndex; int /*<<< orphan*/  Present; int /*<<< orphan*/  IntType; int /*<<< orphan*/  Attributes; } ;
struct TYPE_5__ {int Attributes; int /*<<< orphan*/  IRQInfo1; } ;
struct TYPE_4__ {int NumPorts1; int NumPorts2; int IOAddrLines; int /*<<< orphan*/  Attributes2; int /*<<< orphan*/  Attributes1; } ;
struct pcmcia_device {TYPE_3__ conf; TYPE_2__ irq; TYPE_1__ io; int /*<<< orphan*/ * priv; } ;
typedef  int /*<<< orphan*/  local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_16 ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 int IRQ_FIRST_SHARED ; 
 int /*<<< orphan*/  IRQ_LEVEL_ID ; 
 int IRQ_TYPE_DYNAMIC_SHARING ; 
 int IRQ_TYPE_EXCLUSIVE ; 
 int /*<<< orphan*/  PRESENT_OPTION ; 
 int avma1cs_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int avma1cs_probe(struct pcmcia_device *p_dev)
{
    local_info_t *local;

    DEBUG(0, "avma1cs_attach()\n");

    /* Allocate space for private device-specific data */
    local = kzalloc(sizeof(local_info_t), GFP_KERNEL);
    if (!local)
	return -ENOMEM;

    p_dev->priv = local;

    /* The io structure describes IO port mapping */
    p_dev->io.NumPorts1 = 16;
    p_dev->io.Attributes1 = IO_DATA_PATH_WIDTH_8;
    p_dev->io.NumPorts2 = 16;
    p_dev->io.Attributes2 = IO_DATA_PATH_WIDTH_16;
    p_dev->io.IOAddrLines = 5;

    /* Interrupt setup */
    p_dev->irq.Attributes = IRQ_TYPE_EXCLUSIVE;
    p_dev->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING|IRQ_FIRST_SHARED;

    p_dev->irq.IRQInfo1 = IRQ_LEVEL_ID;

    /* General socket configuration */
    p_dev->conf.Attributes = CONF_ENABLE_IRQ;
    p_dev->conf.IntType = INT_MEMORY_AND_IO;
    p_dev->conf.ConfigIndex = 1;
    p_dev->conf.Present = PRESENT_OPTION;

    return avma1cs_config(p_dev);
}
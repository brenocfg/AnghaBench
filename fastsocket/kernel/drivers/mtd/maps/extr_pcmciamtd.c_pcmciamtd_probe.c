#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcmciamtd_dev {struct pcmcia_device* p_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  IntType; scalar_t__ Attributes; } ;
struct pcmcia_device {TYPE_1__ conf; struct pcmciamtd_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,struct pcmciamtd_dev*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INT_MEMORY ; 
 struct pcmciamtd_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pcmciamtd_config (struct pcmcia_device*) ; 

__attribute__((used)) static int pcmciamtd_probe(struct pcmcia_device *link)
{
	struct pcmciamtd_dev *dev;

	/* Create new memory card device */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) return -ENOMEM;
	DEBUG(1, "dev=0x%p", dev);

	dev->p_dev = link;
	link->priv = dev;

	link->conf.Attributes = 0;
	link->conf.IntType = INT_MEMORY;

	return pcmciamtd_config(link);
}
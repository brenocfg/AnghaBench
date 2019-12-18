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
struct pcmcia_device {TYPE_1__* function_config; struct pcmcia_device* devname; int /*<<< orphan*/  socket; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ds_dev_dbg (int,struct device*,char*) ; 
 int /*<<< orphan*/  kfree (struct pcmcia_device*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_put_socket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_release_function ; 
 struct pcmcia_device* to_pcmcia_dev (struct device*) ; 

__attribute__((used)) static void pcmcia_release_dev(struct device *dev)
{
	struct pcmcia_device *p_dev = to_pcmcia_dev(dev);
	ds_dev_dbg(1, dev, "releasing device\n");
	pcmcia_put_socket(p_dev->socket);
	kfree(p_dev->devname);
	kref_put(&p_dev->function_config->ref, pcmcia_release_function);
	kfree(p_dev);
}
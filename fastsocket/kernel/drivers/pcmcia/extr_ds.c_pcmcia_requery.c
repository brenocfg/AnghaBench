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
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct pcmcia_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ds_dev_dbg (int,struct device*,char*) ; 
 int /*<<< orphan*/  pcmcia_device_query (struct pcmcia_device*) ; 
 struct pcmcia_device* to_pcmcia_dev (struct device*) ; 

__attribute__((used)) static int pcmcia_requery(struct device *dev, void * _data)
{
	struct pcmcia_device *p_dev = to_pcmcia_dev(dev);
	if (!p_dev->dev.driver) {
		ds_dev_dbg(1, dev, "update device information\n");
		pcmcia_device_query(p_dev);
	}

	return 0;
}
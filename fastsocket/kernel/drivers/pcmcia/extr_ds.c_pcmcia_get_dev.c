#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pcmcia_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* get_device (int /*<<< orphan*/ *) ; 
 struct pcmcia_device* to_pcmcia_dev (struct device*) ; 

struct pcmcia_device * pcmcia_get_dev(struct pcmcia_device *p_dev)
{
	struct device *tmp_dev;
	tmp_dev = get_device(&p_dev->dev);
	if (!tmp_dev)
		return NULL;
	return to_pcmcia_dev(tmp_dev);
}
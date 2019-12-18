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
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  assabet_pcmcia_ops ; 
 int /*<<< orphan*/  machine_has_neponset () ; 
 scalar_t__ machine_is_assabet () ; 
 int sa11xx_drv_pcmcia_probe (struct device*,int /*<<< orphan*/ *,int,int) ; 

int pcmcia_assabet_init(struct device *dev)
{
	int ret = -ENODEV;

	if (machine_is_assabet() && !machine_has_neponset())
		ret = sa11xx_drv_pcmcia_probe(dev, &assabet_pcmcia_ops, 1, 1);

	return ret;
}
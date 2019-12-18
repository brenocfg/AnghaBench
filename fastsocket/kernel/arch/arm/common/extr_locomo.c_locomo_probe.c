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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int __locomo_probe (int /*<<< orphan*/ *,struct resource*,int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int locomo_probe(struct platform_device *dev)
{
	struct resource *mem;
	int irq;

	mem = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!mem)
		return -EINVAL;
	irq = platform_get_irq(dev, 0);
	if (irq < 0)
		return -ENXIO;

	return __locomo_probe(&dev->dev, mem, irq);
}
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
struct resource {int start; int end; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct platform_device*) ; 
 int /*<<< orphan*/  sh_mobile_i2c_isr ; 

__attribute__((used)) static int sh_mobile_i2c_hook_irqs(struct platform_device *dev, int hook)
{
	struct resource *res;
	int ret = -ENXIO;
	int q, m;
	int k = 0;
	int n = 0;

	while ((res = platform_get_resource(dev, IORESOURCE_IRQ, k))) {
		for (n = res->start; hook && n <= res->end; n++) {
			if (request_irq(n, sh_mobile_i2c_isr, IRQF_DISABLED,
					dev_name(&dev->dev), dev))
				goto rollback;
		}
		k++;
	}

	if (hook)
		return k > 0 ? 0 : -ENOENT;

	k--;
	ret = 0;

 rollback:
	for (q = k; k >= 0; k--) {
		for (m = n; m >= res->start; m--)
			free_irq(m, dev);

		res = platform_get_resource(dev, IORESOURCE_IRQ, k - 1);
		m = res->end;
	}

	return ret;
}
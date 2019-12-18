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
struct platform_device {int num_resources; struct resource* resource; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long IORESOURCE_IO ; 
 unsigned long IORESOURCE_MEM ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 
 unsigned long resource_type (struct resource*) ; 

void platform_device_del(struct platform_device *pdev)
{
	int i;

	if (pdev) {
		device_del(&pdev->dev);

		for (i = 0; i < pdev->num_resources; i++) {
			struct resource *r = &pdev->resource[i];
			unsigned long type = resource_type(r);

			if (type == IORESOURCE_MEM || type == IORESOURCE_IO)
				release_resource(r);
		}
	}
}
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
struct v3020_platform_data {int /*<<< orphan*/  leftshift; } ;
struct v3020 {int /*<<< orphan*/ * ioaddress; int /*<<< orphan*/  leftshift; } ;
struct platform_device {int num_resources; TYPE_1__* resource; } ;
struct TYPE_2__ {scalar_t__ flags; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IORESOURCE_MEM ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int v3020_mmio_map(struct v3020 *chip, struct platform_device *pdev,
			  struct v3020_platform_data *pdata)
{
	if (pdev->num_resources != 1)
		return -EBUSY;

	if (pdev->resource[0].flags != IORESOURCE_MEM)
		return -EBUSY;

	chip->leftshift = pdata->leftshift;
	chip->ioaddress = ioremap(pdev->resource[0].start, 1);
	if (chip->ioaddress == NULL)
		return -EBUSY;

	return 0;
}
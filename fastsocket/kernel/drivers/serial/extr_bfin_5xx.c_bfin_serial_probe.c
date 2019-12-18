#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int flags; scalar_t__ start; } ;
struct platform_device {int num_resources; int /*<<< orphan*/  dev; struct resource* resource; } ;
struct TYPE_3__ {scalar_t__ mapbase; int /*<<< orphan*/ * dev; } ;
struct TYPE_4__ {TYPE_1__ port; } ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 TYPE_2__* bfin_serial_ports ; 
 int /*<<< orphan*/  bfin_serial_reg ; 
 int nr_active_ports ; 
 int /*<<< orphan*/  uart_add_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int bfin_serial_probe(struct platform_device *dev)
{
	struct resource *res = dev->resource;
	int i;

	for (i = 0; i < dev->num_resources; i++, res++)
		if (res->flags & IORESOURCE_MEM)
			break;

	if (i < dev->num_resources) {
		for (i = 0; i < nr_active_ports; i++, res++) {
			if (bfin_serial_ports[i].port.mapbase != res->start)
				continue;
			bfin_serial_ports[i].port.dev = &dev->dev;
			uart_add_one_port(&bfin_serial_reg, &bfin_serial_ports[i].port);
		}
	}

	return 0;
}
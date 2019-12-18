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
struct resource {int start; } ;
struct pnp_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pnp_dbg (int /*<<< orphan*/ *,char*,unsigned long) ; 
 scalar_t__ pnp_resource_enabled (struct resource*) ; 

__attribute__((used)) static void pnpbios_encode_irq(struct pnp_dev *dev, unsigned char *p,
			       struct resource *res)
{
	unsigned long map;

	if (pnp_resource_enabled(res))
		map = 1 << res->start;
	else
		map = 0;

	p[1] = map & 0xff;
	p[2] = (map >> 8) & 0xff;

	pnp_dbg(&dev->dev, "  encode irq mask %#lx\n", map);
}
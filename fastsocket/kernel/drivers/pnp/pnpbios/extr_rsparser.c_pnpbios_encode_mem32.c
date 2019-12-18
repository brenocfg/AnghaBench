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
struct resource {unsigned long start; int end; } ;
struct pnp_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pnp_dbg (int /*<<< orphan*/ *,char*,unsigned long,unsigned long) ; 
 scalar_t__ pnp_resource_enabled (struct resource*) ; 

__attribute__((used)) static void pnpbios_encode_mem32(struct pnp_dev *dev, unsigned char *p,
				 struct resource *res)
{
	unsigned long base;
	unsigned long len;

	if (pnp_resource_enabled(res)) {
		base = res->start;
		len = res->end - res->start + 1;
	} else {
		base = 0;
		len = 0;
	}

	p[4] = base & 0xff;
	p[5] = (base >> 8) & 0xff;
	p[6] = (base >> 16) & 0xff;
	p[7] = (base >> 24) & 0xff;
	p[8] = base & 0xff;
	p[9] = (base >> 8) & 0xff;
	p[10] = (base >> 16) & 0xff;
	p[11] = (base >> 24) & 0xff;
	p[16] = len & 0xff;
	p[17] = (len >> 8) & 0xff;
	p[18] = (len >> 16) & 0xff;
	p[19] = (len >> 24) & 0xff;

	pnp_dbg(&dev->dev, "  encode mem32 %#lx-%#lx\n", base, base + len - 1);
}
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
struct resource {int flags; int end; int start; } ;
struct device_node {int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int macio_resource_quirks(struct device_node *np, struct resource *res,
				 int index)
{
	/* Only quirks for memory resources for now */
	if ((res->flags & IORESOURCE_MEM) == 0)
		return 0;

	/* Grand Central has too large resource 0 on some machines */
	if (index == 0 && !strcmp(np->name, "gc"))
		res->end = res->start + 0x1ffff;

	/* Airport has bogus resource 2 */
	if (index >= 2 && !strcmp(np->name, "radio"))
		return 1;

#ifndef CONFIG_PPC64
	/* DBDMAs may have bogus sizes */
	if ((res->start & 0x0001f000) == 0x00008000)
		res->end = res->start + 0xff;
#endif /* CONFIG_PPC64 */

	/* ESCC parent eats child resources. We could have added a
	 * level of hierarchy, but I don't really feel the need
	 * for it
	 */
	if (!strcmp(np->name, "escc"))
		return 1;

	/* ESCC has bogus resources >= 3 */
	if (index >= 3 && !(strcmp(np->name, "ch-a") &&
			    strcmp(np->name, "ch-b")))
		return 1;

	/* Media bay has too many resources, keep only first one */
	if (index > 0 && !strcmp(np->name, "media-bay"))
		return 1;

	/* Some older IDE resources have bogus sizes */
	if (!(strcmp(np->name, "IDE") && strcmp(np->name, "ATA") &&
	      strcmp(np->type, "ide") && strcmp(np->type, "ata"))) {
		if (index == 0 && (res->end - res->start) > 0xfff)
			res->end = res->start + 0xfff;
		if (index == 1 && (res->end - res->start) > 0xff)
			res->end = res->start + 0xff;
	}
	return 0;
}
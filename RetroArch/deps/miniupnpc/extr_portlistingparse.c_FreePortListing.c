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
struct PortMappingParserData {struct PortMapping* l_head; } ;
struct PortMapping {struct PortMapping* l_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct PortMapping*) ; 

void
FreePortListing(struct PortMappingParserData * pdata)
{
	struct PortMapping * pm;
	while((pm = pdata->l_head) != NULL)
	{
		/* remove from list */
		pdata->l_head = pm->l_next;
		free(pm);
	}
}
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
struct PortMappingParserData {scalar_t__ curelt; struct PortMapping* l_head; } ;
struct PortMapping {struct PortMapping* l_next; } ;
struct TYPE_2__ {scalar_t__ code; scalar_t__ str; } ;

/* Variables and functions */
 scalar_t__ PortMappingEltNone ; 
 scalar_t__ PortMappingEntry ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_1__* elements ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ memcmp (char const*,scalar_t__,int) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (scalar_t__) ; 

__attribute__((used)) static void
startelt(void * d, const char * name, int l)
{
	int i;
	struct PortMappingParserData * pdata = (struct PortMappingParserData *)d;
	pdata->curelt = PortMappingEltNone;
	for(i = 0; elements[i].str; i++)
	{
		if(strlen(elements[i].str) == (size_t)l && memcmp(name, elements[i].str, l) == 0)
		{
			pdata->curelt = elements[i].code;
			break;
		}
	}
	if(pdata->curelt == PortMappingEntry)
	{
		struct PortMapping * pm;
		pm = (struct PortMapping*)calloc(1, sizeof(struct PortMapping));
		if(pm == NULL)
		{
			/* malloc error */
#ifdef DEBUG
			fprintf(stderr, "%s: error allocating memory",
			        "startelt");
#endif /* DEBUG */
			return;
		}
		pm->l_next = pdata->l_head;	/* insert in list */
		pdata->l_head = pm;
	}
}
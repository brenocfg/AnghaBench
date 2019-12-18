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
struct NameValueParserData {struct NameValue* l_head; scalar_t__ portListingLength; struct NameValue* portListing; } ;
struct NameValue {struct NameValue* l_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct NameValue*) ; 

void
ClearNameValueList(struct NameValueParserData * pdata)
{
    struct NameValue * nv;
	if(pdata->portListing)
	{
		free(pdata->portListing);
		pdata->portListing = NULL;
		pdata->portListingLength = 0;
	}
    while((nv = pdata->l_head) != NULL)
    {
		pdata->l_head = nv->l_next;
        free(nv);
    }
}
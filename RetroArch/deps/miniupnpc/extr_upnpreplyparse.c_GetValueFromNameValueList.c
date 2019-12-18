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
struct NameValueParserData {struct NameValue* l_head; } ;
struct NameValue {char* value; int /*<<< orphan*/  name; struct NameValue* l_next; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

char *
GetValueFromNameValueList(struct NameValueParserData * pdata,
                          const char * Name)
{
    struct NameValue * nv;
    char * p = NULL;
    for(nv = pdata->l_head;
        (nv != NULL) && (p == NULL);
        nv = nv->l_next)
    {
        if(strcmp(nv->name, Name) == 0)
            p = nv->value;
    }
    return p;
}
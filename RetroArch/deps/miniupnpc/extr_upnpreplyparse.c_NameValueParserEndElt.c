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
struct NameValueParserData {int cdatalen; scalar_t__ topelt; int /*<<< orphan*/ * cdata; struct NameValue* l_head; int /*<<< orphan*/  curelt; } ;
struct NameValue {char* name; char* value; struct NameValue* l_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
NameValueParserEndElt(void * d, const char * name, int l)
{
    struct NameValueParserData * data = (struct NameValueParserData *)d;
    struct NameValue * nv;
	(void)name;
	(void)l;
	if(!data->topelt)
		return;
	if(strcmp(data->curelt, "NewPortListing") != 0)
	{
		int l;
		/* standard case. Limited to n chars strings */
		l = data->cdatalen;
	    nv = (struct NameValue*)malloc(sizeof(struct NameValue));
		if(nv == NULL)
		{
			/* malloc error */
#ifdef DEBUG
			fprintf(stderr, "%s: error allocating memory",
			        "NameValueParserEndElt");
#endif /* DEBUG */
			return;
		}
	    if(l>=(int)sizeof(nv->value))
	        l = sizeof(nv->value) - 1;
	    strncpy(nv->name, data->curelt, 64);
		nv->name[63] = '\0';
		if(data->cdata != NULL)
		{
			memcpy(nv->value, data->cdata, l);
			nv->value[l] = '\0';
		}
		else
		{
			nv->value[0] = '\0';
		}
		nv->l_next = data->l_head;	/* insert in list */
		data->l_head = nv;
	}
	data->cdata = NULL;
	data->cdatalen = 0;
	data->topelt = 0;
}
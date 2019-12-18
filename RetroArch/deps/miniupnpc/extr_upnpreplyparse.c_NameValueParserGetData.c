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
struct NameValueParserData {char* portListing; int portListingLength; char const* cdata; int cdatalen; int /*<<< orphan*/  curelt; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
NameValueParserGetData(void * d, const char * datas, int l)
{
    struct NameValueParserData * data = (struct NameValueParserData *)d;
	if(strcmp(data->curelt, "NewPortListing") == 0)
	{
		/* specific case for NewPortListing which is a XML Document */
		data->portListing = (char*)malloc(l + 1);
		if(!data->portListing)
		{
			/* malloc error */
#ifdef DEBUG
			fprintf(stderr, "%s: error allocating memory",
			        "NameValueParserGetData");
#endif /* DEBUG */
			return;
		}
		memcpy(data->portListing, datas, l);
		data->portListing[l] = '\0';
		data->portListingLength = l;
	}
	else
	{
		/* standard case. */
		data->cdata = datas;
		data->cdatalen = l;
	}
}
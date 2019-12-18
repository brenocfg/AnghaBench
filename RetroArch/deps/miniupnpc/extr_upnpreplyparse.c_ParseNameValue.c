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
struct xmlparser {char const* xmlstart; int xmlsize; scalar_t__ attfunc; int /*<<< orphan*/  datafunc; int /*<<< orphan*/  endeltfunc; int /*<<< orphan*/  starteltfunc; struct NameValueParserData* data; } ;
struct NameValueParserData {scalar_t__ portListingLength; int /*<<< orphan*/ * portListing; int /*<<< orphan*/ * l_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  NameValueParserEndElt ; 
 int /*<<< orphan*/  NameValueParserGetData ; 
 int /*<<< orphan*/  NameValueParserStartElt ; 
 int /*<<< orphan*/  parsexml (struct xmlparser*) ; 

void
ParseNameValue(const char * buffer, int bufsize,
               struct NameValueParserData * data)
{
	struct xmlparser parser;
	data->l_head = NULL;
	data->portListing = NULL;
	data->portListingLength = 0;
	/* init xmlparser object */
	parser.xmlstart = buffer;
	parser.xmlsize = bufsize;
	parser.data = data;
	parser.starteltfunc = NameValueParserStartElt;
	parser.endeltfunc = NameValueParserEndElt;
	parser.datafunc = NameValueParserGetData;
	parser.attfunc = 0;
	parsexml(&parser);
}
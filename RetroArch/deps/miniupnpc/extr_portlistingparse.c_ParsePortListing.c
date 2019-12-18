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
struct xmlparser {char const* xmlstart; int xmlsize; scalar_t__ attfunc; int /*<<< orphan*/  datafunc; int /*<<< orphan*/  endeltfunc; int /*<<< orphan*/  starteltfunc; struct PortMappingParserData* data; } ;
struct PortMappingParserData {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  endelt ; 
 int /*<<< orphan*/  memset (struct PortMappingParserData*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parsexml (struct xmlparser*) ; 
 int /*<<< orphan*/  portlisting_data ; 
 int /*<<< orphan*/  startelt ; 

void
ParsePortListing(const char * buffer, int bufsize,
                 struct PortMappingParserData * pdata)
{
	struct xmlparser parser;

	memset(pdata, 0, sizeof(struct PortMappingParserData));
	/* init xmlparser */
	parser.xmlstart     = buffer;
	parser.xmlsize      = bufsize;
	parser.data         = pdata;
	parser.starteltfunc = startelt;
	parser.endeltfunc   = endelt;
	parser.datafunc     = portlisting_data;
	parser.attfunc      = 0;
	parsexml(&parser);
}
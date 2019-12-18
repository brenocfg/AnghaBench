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
struct xmlparser {scalar_t__ xmlsize; scalar_t__ xmlstart; scalar_t__ xmlend; scalar_t__ xml; } ;

/* Variables and functions */
 int /*<<< orphan*/  parseelt (struct xmlparser*) ; 

void parsexml(struct xmlparser * parser)
{
	parser->xml = parser->xmlstart;
	parser->xmlend = parser->xmlstart + parser->xmlsize;
	parseelt(parser);
}
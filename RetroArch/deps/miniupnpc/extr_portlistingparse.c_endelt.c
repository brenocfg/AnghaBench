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
struct PortMappingParserData {int /*<<< orphan*/  curelt; } ;

/* Variables and functions */
 int /*<<< orphan*/  PortMappingEltNone ; 

__attribute__((used)) static void
endelt(void * d, const char * name, int l)
{
	struct PortMappingParserData * pdata = (struct PortMappingParserData *)d;
	(void)name;
	(void)l;
	pdata->curelt = PortMappingEltNone;
}
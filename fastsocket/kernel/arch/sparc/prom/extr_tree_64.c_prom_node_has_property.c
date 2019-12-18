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

/* Variables and functions */
 int /*<<< orphan*/  prom_nextprop (int,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

int prom_node_has_property(int node, const char *prop)
{
	char buf [32];
        
	*buf = 0;
	do {
		prom_nextprop(node, buf, buf);
		if(!strcmp(buf, prop))
			return 1;
	} while (*buf);
	return 0;
}
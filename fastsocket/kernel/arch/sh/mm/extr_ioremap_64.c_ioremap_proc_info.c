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
struct resource {char* name; scalar_t__ end; scalar_t__ start; struct resource* sibling; struct resource* child; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long,unsigned long,char const*) ; 

__attribute__((used)) static int
ioremap_proc_info(char *buf, char **start, off_t fpos, int length, int *eof,
		  void *data)
{
	char *p = buf, *e = buf + length;
	struct resource *r;
	const char *nm;

	for (r = ((struct resource *)data)->child; r != NULL; r = r->sibling) {
		if (p + 32 >= e)        /* Better than nothing */
			break;
		nm = r->name;
		if (nm == NULL)
			nm = "???";

		p += sprintf(p, "%08lx-%08lx: %s\n",
			     (unsigned long)r->start,
			     (unsigned long)r->end, nm);
	}

	return p-buf;
}
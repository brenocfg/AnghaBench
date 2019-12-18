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
struct fdt_node_header {int dummy; } ;

/* Variables and functions */
 int ALIGN (scalar_t__) ; 
 int FDT_TAGSIZE ; 
 char* _realloc_fdt (char*,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *realloc_node(char *fdt, const char *name)
{
	int delta;
	/* FDT_BEGIN_NODE, node name in off_struct and FDT_END_NODE */
	delta = sizeof(struct fdt_node_header) + ALIGN(strlen(name) + 1)
			+ FDT_TAGSIZE;
	return _realloc_fdt(fdt, delta);
}
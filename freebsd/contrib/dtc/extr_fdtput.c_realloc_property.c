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
struct fdt_property {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int) ; 
 char* _realloc_fdt (char*,int) ; 
 int /*<<< orphan*/  fdt_get_property (char*,int,char const*,int*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *realloc_property(char *fdt, int nodeoffset,
		const char *name, int newlen)
{
	int delta = 0;
	int oldlen = 0;

	if (!fdt_get_property(fdt, nodeoffset, name, &oldlen))
		/* strings + property header */
		delta = sizeof(struct fdt_property) + strlen(name) + 1;

	if (newlen > oldlen)
		/* actual value in off_struct */
		delta += ALIGN(newlen) - ALIGN(oldlen);

	return _realloc_fdt(fdt, delta);
}
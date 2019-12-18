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
 int FDT_ERR_NOSPACE ; 
 void* fdt_getprop (void*,int,char const*,int*) ; 
 int fdt_setprop_inplace_namelen_partial (void*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int fdt_setprop_inplace(void *fdt, int nodeoffset, const char *name,
			const void *val, int len)
{
	const void *propval;
	int proplen;

	propval = fdt_getprop(fdt, nodeoffset, name, &proplen);
	if (! propval)
		return proplen;

	if (proplen != len)
		return -FDT_ERR_NOSPACE;

	return fdt_setprop_inplace_namelen_partial(fdt, nodeoffset, name,
						   strlen(name), 0,
						   val, len);
}
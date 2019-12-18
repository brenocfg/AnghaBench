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
 char const* fdt_getprop_namelen (void const*,int,char const*,int,int /*<<< orphan*/ *) ; 
 int fdt_path_offset (void const*,char*) ; 

const char *fdt_get_alias_namelen(const void *fdt,
				  const char *name, int namelen)
{
	int aliasoffset;

	aliasoffset = fdt_path_offset(fdt, "/aliases");
	if (aliasoffset < 0)
		return NULL;

	return fdt_getprop_namelen(fdt, aliasoffset, name, namelen, NULL);
}
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
struct fdt_node_header {char const* name; } ;

/* Variables and functions */
 int _fdt_check_node_offset (void const*,int) ; 
 struct fdt_node_header* _fdt_offset_ptr (void const*,int) ; 
 int fdt_check_header (void const*) ; 
 int strlen (char const*) ; 

const char *fdt_get_name(const void *fdt, int nodeoffset, int *len)
{
	const struct fdt_node_header *nh = _fdt_offset_ptr(fdt, nodeoffset);
	int err;

	if (((err = fdt_check_header(fdt)) != 0)
	    || ((err = _fdt_check_node_offset(fdt, nodeoffset)) < 0))
			goto fail;

	if (len)
		*len = strlen(nh->name);

	return nh->name;

 fail:
	if (len)
		*len = err;
	return NULL;
}
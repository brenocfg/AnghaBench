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
struct fdt_property {void* len; void* nameoff; void* tag; } ;

/* Variables and functions */
 int FDT_PROP ; 
 int FDT_TAGALIGN (int) ; 
 int _fdt_check_node_offset (void*,int) ; 
 int _fdt_find_add_string (void*,char const*) ; 
 struct fdt_property* _fdt_offset_ptr_w (void*,int) ; 
 int _fdt_splice_struct (void*,struct fdt_property*,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_fdt32 (int) ; 

__attribute__((used)) static int _fdt_add_property(void *fdt, int nodeoffset, const char *name,
			     int len, struct fdt_property **prop)
{
	int proplen;
	int nextoffset;
	int namestroff;
	int err;

	if ((nextoffset = _fdt_check_node_offset(fdt, nodeoffset)) < 0)
		return nextoffset;

	namestroff = _fdt_find_add_string(fdt, name);
	if (namestroff < 0)
		return namestroff;

	*prop = _fdt_offset_ptr_w(fdt, nextoffset);
	proplen = sizeof(**prop) + FDT_TAGALIGN(len);

	err = _fdt_splice_struct(fdt, *prop, 0, proplen);
	if (err)
		return err;

	(*prop)->tag = cpu_to_fdt32(FDT_PROP);
	(*prop)->nameoff = cpu_to_fdt32(namestroff);
	(*prop)->len = cpu_to_fdt32(len);
	return 0;
}
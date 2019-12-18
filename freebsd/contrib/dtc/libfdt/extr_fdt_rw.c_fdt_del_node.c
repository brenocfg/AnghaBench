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
 int /*<<< orphan*/  FDT_RW_CHECK_HEADER (void*) ; 
 int _fdt_node_end_offset (void*,int) ; 
 int /*<<< orphan*/  _fdt_offset_ptr_w (void*,int) ; 
 int _fdt_splice_struct (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int fdt_del_node(void *fdt, int nodeoffset)
{
	int endoffset;

	FDT_RW_CHECK_HEADER(fdt);

	endoffset = _fdt_node_end_offset(fdt, nodeoffset);
	if (endoffset < 0)
		return endoffset;

	return _fdt_splice_struct(fdt, _fdt_offset_ptr_w(fdt, nodeoffset),
				  endoffset - nodeoffset, 0);
}
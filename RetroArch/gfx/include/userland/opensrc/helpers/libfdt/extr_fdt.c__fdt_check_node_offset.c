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
 scalar_t__ FDT_BEGIN_NODE ; 
 int FDT_ERR_BADOFFSET ; 
 int FDT_TAGSIZE ; 
 scalar_t__ fdt_next_tag (void const*,int,int*) ; 

int _fdt_check_node_offset(const void *fdt, int offset)
{
	if ((offset < 0) || (offset % FDT_TAGSIZE)
	    || (fdt_next_tag(fdt, offset, &offset) != FDT_BEGIN_NODE))
		return -FDT_ERR_BADOFFSET;

	return offset;
}
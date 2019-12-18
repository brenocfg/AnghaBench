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
typedef  int uint32_t ;

/* Variables and functions */
#define  FDT_BEGIN_NODE 132 
#define  FDT_END 131 
#define  FDT_END_NODE 130 
 int FDT_ERR_BADOFFSET ; 
 int FDT_ERR_BADSTRUCTURE ; 
#define  FDT_NOP 129 
#define  FDT_PROP 128 
 int fdt_next_tag (void*,int,int*) ; 

int _fdt_node_end_offset(void *fdt, int nodeoffset)
{
	int level = 0;
	uint32_t tag;
	int offset, nextoffset;

	tag = fdt_next_tag(fdt, nodeoffset, &nextoffset);
	if (tag != FDT_BEGIN_NODE)
		return -FDT_ERR_BADOFFSET;
	do {
		offset = nextoffset;
		tag = fdt_next_tag(fdt, offset, &nextoffset);

		switch (tag) {
		case FDT_END:
			return offset;

		case FDT_BEGIN_NODE:
			level++;
			break;

		case FDT_END_NODE:
			level--;
			break;

		case FDT_PROP:
		case FDT_NOP:
			break;

		default:
			return -FDT_ERR_BADSTRUCTURE;
		}
	} while (level >= 0);

	return nextoffset;
}
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
typedef  scalar_t__ uint32_t ;
struct fdt_node_header {int /*<<< orphan*/  name; void* tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDT_BEGIN_NODE ; 
 int /*<<< orphan*/  FDT_END_NODE ; 
 int FDT_ERR_EXISTS ; 
 int FDT_ERR_NOTFOUND ; 
 scalar_t__ FDT_NOP ; 
 scalar_t__ FDT_PROP ; 
 int /*<<< orphan*/  FDT_RW_CHECK_HEADER (void*) ; 
 int FDT_TAGALIGN (int) ; 
 int FDT_TAGSIZE ; 
 struct fdt_node_header* _fdt_offset_ptr_w (void*,int) ; 
 int _fdt_splice_struct (void*,struct fdt_node_header*,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_fdt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ fdt_next_tag (void*,int,int*) ; 
 int fdt_subnode_offset_namelen (void*,int,char const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int fdt_add_subnode_namelen(void *fdt, int parentoffset,
			    const char *name, int namelen)
{
	struct fdt_node_header *nh;
	int offset, nextoffset;
	int nodelen;
	int err;
	uint32_t tag;
	uint32_t *endtag;

	FDT_RW_CHECK_HEADER(fdt);

	offset = fdt_subnode_offset_namelen(fdt, parentoffset, name, namelen);
	if (offset >= 0)
		return -FDT_ERR_EXISTS;
	else if (offset != -FDT_ERR_NOTFOUND)
		return offset;

	/* Try to place the new node after the parent's properties */
	fdt_next_tag(fdt, parentoffset, &nextoffset); /* skip the BEGIN_NODE */
	do {
		offset = nextoffset;
		tag = fdt_next_tag(fdt, offset, &nextoffset);
	} while ((tag == FDT_PROP) || (tag == FDT_NOP));

	nh = _fdt_offset_ptr_w(fdt, offset);
	nodelen = sizeof(*nh) + FDT_TAGALIGN(namelen+1) + FDT_TAGSIZE;

	err = _fdt_splice_struct(fdt, nh, 0, nodelen);
	if (err)
		return err;

	nh->tag = cpu_to_fdt32(FDT_BEGIN_NODE);
	memset(nh->name, 0, FDT_TAGALIGN(namelen+1));
	memcpy(nh->name, name, namelen);
	endtag = (uint32_t *)((char *)nh + nodelen - FDT_TAGSIZE);
	*endtag = cpu_to_fdt32(FDT_END_NODE);

	return offset;
}
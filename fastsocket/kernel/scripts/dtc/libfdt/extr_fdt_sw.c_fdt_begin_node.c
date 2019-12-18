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
struct fdt_node_header {int /*<<< orphan*/  name; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDT_BEGIN_NODE ; 
 int FDT_ERR_NOSPACE ; 
 int /*<<< orphan*/  FDT_SW_CHECK_HEADER (void*) ; 
 scalar_t__ FDT_TAGALIGN (int) ; 
 struct fdt_node_header* _fdt_grab_space (void*,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_fdt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char const*) ; 

int fdt_begin_node(void *fdt, const char *name)
{
	struct fdt_node_header *nh;
	int namelen = strlen(name) + 1;

	FDT_SW_CHECK_HEADER(fdt);

	nh = _fdt_grab_space(fdt, sizeof(*nh) + FDT_TAGALIGN(namelen));
	if (! nh)
		return -FDT_ERR_NOSPACE;

	nh->tag = cpu_to_fdt32(FDT_BEGIN_NODE);
	memcpy(nh->name, name, namelen);
	return 0;
}
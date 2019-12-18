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

/* Variables and functions */
 int FDT_ERR_BADOVERLAY ; 
 int FDT_ERR_BADPHANDLE ; 
 int FDT_ERR_NOTFOUND ; 
 char* fdt_getprop (void const*,int,char*,int*) ; 
 int fdt_node_offset_by_phandle (void const*,scalar_t__) ; 
 int fdt_path_offset (void const*,char const*) ; 
 scalar_t__ overlay_get_target_phandle (void const*,int) ; 

__attribute__((used)) static int overlay_get_target(const void *fdt, const void *fdto,
			      int fragment)
{
	uint32_t phandle;
	const char *path;
	int path_len;

	/* Try first to do a phandle based lookup */
	phandle = overlay_get_target_phandle(fdto, fragment);
	if (phandle == (uint32_t)-1)
		return -FDT_ERR_BADPHANDLE;

	if (phandle)
		return fdt_node_offset_by_phandle(fdt, phandle);

	/* And then a path based lookup */
	path = fdt_getprop(fdto, fragment, "target-path", &path_len);
	if (!path) {
		/*
		 * If we haven't found either a target or a
		 * target-path property in a node that contains a
		 * __overlay__ subnode (we wouldn't be called
		 * otherwise), consider it a improperly written
		 * overlay
		 */
		if (path_len == -FDT_ERR_NOTFOUND)
			return -FDT_ERR_BADOVERLAY;

		return path_len;
	}

	return fdt_path_offset(fdt, path);
}
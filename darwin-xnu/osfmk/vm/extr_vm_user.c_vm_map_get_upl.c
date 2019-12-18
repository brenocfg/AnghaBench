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
typedef  int /*<<< orphan*/  vm_tag_t ;
typedef  scalar_t__ vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  upl_t ;
typedef  int /*<<< orphan*/  upl_size_t ;
typedef  int /*<<< orphan*/  upl_page_info_array_t ;
typedef  int upl_control_flags_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int UPL_FORCE_DATA_SYNC ; 
 int UPL_NOZEROFILL ; 
 scalar_t__ VM_MAP_NULL ; 
 int /*<<< orphan*/  vm_map_create_upl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*,int*,int /*<<< orphan*/ ) ; 

kern_return_t
vm_map_get_upl(
	vm_map_t		map,
	vm_map_offset_t		map_offset,
	upl_size_t		*upl_size,
	upl_t			*upl,
	upl_page_info_array_t	page_list,
	unsigned int		*count,
	upl_control_flags_t	*flags,
	vm_tag_t        	tag,
	int             	force_data_sync)
{
	upl_control_flags_t map_flags;
	kern_return_t	    kr;

	if (VM_MAP_NULL == map)
		return KERN_INVALID_ARGUMENT;

	map_flags = *flags & ~UPL_NOZEROFILL;
	if (force_data_sync)
		map_flags |= UPL_FORCE_DATA_SYNC;

	kr = vm_map_create_upl(map,
			       map_offset,
			       upl_size,
			       upl,
			       page_list,
			       count,
			       &map_flags,
			       tag);

	*flags = (map_flags & ~UPL_FORCE_DATA_SYNC);
	return kr;
}
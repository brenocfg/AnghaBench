#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_map_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {scalar_t__ nentries; int page_shift; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 

kern_return_t
vm_map_set_page_shift(
	vm_map_t  	map,
	int		pageshift)
{
	if (map->hdr.nentries != 0) {
		/* too late to change page size */
		return KERN_FAILURE;
	}

	map->hdr.page_shift = pageshift;

	return KERN_SUCCESS;
}
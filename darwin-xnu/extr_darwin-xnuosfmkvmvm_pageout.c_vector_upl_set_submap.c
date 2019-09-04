#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  TYPE_1__* vector_upl_t ;
typedef  TYPE_2__* upl_t ;
struct TYPE_6__ {TYPE_1__* vector_upl; } ;
struct TYPE_5__ {int /*<<< orphan*/  submap_dst_addr; int /*<<< orphan*/  submap; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ vector_upl_is_valid (TYPE_2__*) ; 

void
vector_upl_set_submap(upl_t upl, vm_map_t submap, vm_offset_t submap_dst_addr)
{
	if(vector_upl_is_valid(upl)) {
		vector_upl_t vector_upl = upl->vector_upl;
		if(vector_upl) {
			vector_upl->submap = submap;
			vector_upl->submap_dst_addr = submap_dst_addr;
		}
		else
			panic("vector_upl_get_submap was passed a non-vectored UPL\n");
	}
	else
		panic("vector_upl_get_submap was passed a NULL UPL\n");
}
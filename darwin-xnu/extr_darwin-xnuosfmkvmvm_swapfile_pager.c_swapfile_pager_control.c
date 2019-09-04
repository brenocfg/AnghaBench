#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* swapfile_pager_t ;
typedef  TYPE_3__* memory_object_t ;
typedef  int /*<<< orphan*/  memory_object_control_t ;
struct TYPE_10__ {int /*<<< orphan*/ * mo_pager_ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  mo_control; } ;
struct TYPE_9__ {TYPE_1__ swp_pgr_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMORY_OBJECT_CONTROL_NULL ; 
 TYPE_3__* MEMORY_OBJECT_NULL ; 
 TYPE_2__* swapfile_pager_lookup (TYPE_3__*) ; 
 int /*<<< orphan*/  swapfile_pager_ops ; 

memory_object_control_t
swapfile_pager_control(
	memory_object_t	mem_obj)
{
	swapfile_pager_t	pager;

	if (mem_obj == MEMORY_OBJECT_NULL ||
	    mem_obj->mo_pager_ops != &swapfile_pager_ops) {
		return MEMORY_OBJECT_CONTROL_NULL;
	}
	pager = swapfile_pager_lookup(mem_obj);
	return pager->swp_pgr_hdr.mo_control;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* vm_page_iterate_proc ) (int /*<<< orphan*/ *,unsigned int,TYPE_1__*) ;
typedef  TYPE_1__* vm_object_t ;
typedef  int /*<<< orphan*/  queue_entry_t ;
typedef  TYPE_3__* purgeable_q_t ;
typedef  int /*<<< orphan*/  mach_memory_info_t ;
struct TYPE_7__ {int /*<<< orphan*/ * objq; } ;
struct TYPE_6__ {int /*<<< orphan*/  objq; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void 
vm_page_iterate_purgeable_objects(mach_memory_info_t * info, unsigned int num_info,
				  vm_page_iterate_proc proc, purgeable_q_t queue, 
				  int group)
{
    vm_object_t object;

    for (object = (vm_object_t) queue_first(&queue->objq[group]);
		!queue_end(&queue->objq[group], (queue_entry_t) object);
		object = (vm_object_t) queue_next(&object->objq))
    {
		proc(info, num_info, object);
    }
}
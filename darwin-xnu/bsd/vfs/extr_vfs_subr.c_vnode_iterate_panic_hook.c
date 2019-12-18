#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct vnode_iterate_panic_hook {scalar_t__ mp; scalar_t__ vp; } ;
struct TYPE_3__ {scalar_t__ len; scalar_t__ phys_start; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ panic_phys_range_t ;
typedef  int /*<<< orphan*/  panic_hook_t ;

/* Variables and functions */
 int /*<<< orphan*/  panic_dump_mem (void*,int) ; 
 scalar_t__ panic_phys_range_before (scalar_t__,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  paniclog_append_noflush (char*,scalar_t__,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void vnode_iterate_panic_hook(panic_hook_t *hook_)
{
	struct vnode_iterate_panic_hook *hook = (struct vnode_iterate_panic_hook *)hook_;
	panic_phys_range_t range;
	uint64_t phys;
	
	if (panic_phys_range_before(hook->mp, &phys, &range)) {
		paniclog_append_noflush("mp = %p, phys = %p, prev (%p: %p-%p)\n",
				hook->mp, phys, range.type, range.phys_start,
				range.phys_start + range.len);
	} else {
		paniclog_append_noflush("mp = %p, phys = %p, prev (!)\n", hook->mp, phys);
	}

	if (panic_phys_range_before(hook->vp, &phys, &range)) {
		paniclog_append_noflush("vp = %p, phys = %p, prev (%p: %p-%p)\n",
				hook->vp, phys, range.type, range.phys_start,
				range.phys_start + range.len);
	} else {
		paniclog_append_noflush("vp = %p, phys = %p, prev (!)\n", hook->vp, phys);
	}
	panic_dump_mem((void *)(((vm_offset_t)hook->mp -4096) & ~4095), 12288);
}
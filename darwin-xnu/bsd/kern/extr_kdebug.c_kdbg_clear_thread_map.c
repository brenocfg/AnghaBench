#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct TYPE_2__ {int kdebug_flags; } ;

/* Variables and functions */
 int KDBG_MAPINIT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ kd_ctrl_page ; 
 scalar_t__ kd_mapcount ; 
 int /*<<< orphan*/ * kd_mapptr ; 
 scalar_t__ kd_mapsize ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ktrace_assert_lock_held () ; 

__attribute__((used)) static void
kdbg_clear_thread_map(void)
{
	ktrace_assert_lock_held();

	if (kd_ctrl_page.kdebug_flags & KDBG_MAPINIT) {
		assert(kd_mapptr != NULL);
		kmem_free(kernel_map, (vm_offset_t)kd_mapptr, kd_mapsize);
		kd_mapptr = NULL;
		kd_mapsize = 0;
		kd_mapcount = 0;
		kd_ctrl_page.kdebug_flags &= ~KDBG_MAPINIT;
	}
}
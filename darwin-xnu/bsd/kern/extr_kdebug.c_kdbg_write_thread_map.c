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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/ * vfs_context_t ;
typedef  int boolean_t ;
struct TYPE_2__ {int kdebug_flags; } ;

/* Variables and functions */
 int ENODATA ; 
 int KDBG_MAPINIT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ kd_ctrl_page ; 
 int /*<<< orphan*/  kdbg_clear_thread_map () ; 
 int kdbg_write_v1_header (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktrace_assert_lock_held () ; 

__attribute__((used)) static int
kdbg_write_thread_map(vnode_t vp, vfs_context_t ctx)
{
	int ret = 0;
	boolean_t map_initialized;

	ktrace_assert_lock_held();
	assert(ctx != NULL);

	map_initialized = (kd_ctrl_page.kdebug_flags & KDBG_MAPINIT);

	ret = kdbg_write_v1_header(map_initialized, vp, ctx);
	if (ret == 0) {
		if (map_initialized) {
			kdbg_clear_thread_map();
		} else {
			ret = ENODATA;
		}
	}

	return ret;
}
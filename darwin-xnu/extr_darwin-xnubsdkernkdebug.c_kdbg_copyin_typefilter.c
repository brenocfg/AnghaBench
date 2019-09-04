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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/ * typefilter_t ;
struct TYPE_2__ {int /*<<< orphan*/  kdebug_iops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_TRACE ; 
 int EINVAL ; 
 int ENOMEM ; 
 size_t KDBG_TYPEFILTER_BITMAP_SIZE ; 
 int /*<<< orphan*/  KD_CALLBACK_TYPEFILTER_CHANGED ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__ kd_ctrl_page ; 
 int /*<<< orphan*/  kdbg_enable_typefilter () ; 
 int kdbg_initialize_typefilter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kdbg_iop_list_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdbg_typefilter ; 
 int /*<<< orphan*/  ktrace_assert_lock_held () ; 
 int /*<<< orphan*/  typefilter_allow_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typefilter_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * typefilter_create () ; 
 int /*<<< orphan*/  typefilter_deallocate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kdbg_copyin_typefilter(user_addr_t addr, size_t size)
{
	int ret = ENOMEM;
	typefilter_t tf;

	ktrace_assert_lock_held();

	if (size != KDBG_TYPEFILTER_BITMAP_SIZE) {
		return EINVAL;
	}

	if ((tf = typefilter_create())) {
		if ((ret = copyin(addr, tf, KDBG_TYPEFILTER_BITMAP_SIZE)) == 0) {
			/* The kernel typefilter must always allow DBG_TRACE */
			typefilter_allow_class(tf, DBG_TRACE);

			/*
			 * If this is the first typefilter; claim it.
			 * Otherwise copy and deallocate.
			 *
			 * Allocating a typefilter for the copyin allows
			 * the kernel to hold the invariant that DBG_TRACE
			 * must always be allowed. 
			 */
			if (!kdbg_typefilter) {
				if ((ret = kdbg_initialize_typefilter(tf))) {
					return ret;
				}
				tf = NULL;
			} else {
				typefilter_copy(kdbg_typefilter, tf);
			}

			kdbg_enable_typefilter();
			kdbg_iop_list_callback(kd_ctrl_page.kdebug_iops, KD_CALLBACK_TYPEFILTER_CHANGED, kdbg_typefilter);
		}

		if (tf)
			typefilter_deallocate(tf);
	}

	return ret;
}
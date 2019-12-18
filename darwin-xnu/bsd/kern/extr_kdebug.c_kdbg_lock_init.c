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
typedef  int /*<<< orphan*/  lck_grp_t ;
typedef  int /*<<< orphan*/  lck_grp_attr_t ;
typedef  int /*<<< orphan*/  lck_attr_t ;
struct TYPE_2__ {int kdebug_flags; } ;

/* Variables and functions */
 int KDBG_LOCKINIT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ kd_ctrl_page ; 
 void* kds_spin_lock ; 
 void* kdw_spin_lock ; 
 int /*<<< orphan*/ * lck_attr_alloc_init () ; 
 int /*<<< orphan*/ * lck_grp_alloc_init (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lck_grp_attr_alloc_init () ; 
 void* lck_spin_alloc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
kdbg_lock_init(void)
{
	static lck_grp_attr_t *kdebug_lck_grp_attr = NULL;
	static lck_grp_t      *kdebug_lck_grp      = NULL;
	static lck_attr_t     *kdebug_lck_attr     = NULL;

	if (kd_ctrl_page.kdebug_flags & KDBG_LOCKINIT) {
		return;
	}

	assert(kdebug_lck_grp_attr == NULL);
	kdebug_lck_grp_attr = lck_grp_attr_alloc_init();
	kdebug_lck_grp = lck_grp_alloc_init("kdebug", kdebug_lck_grp_attr);
	kdebug_lck_attr = lck_attr_alloc_init();

	kds_spin_lock = lck_spin_alloc_init(kdebug_lck_grp, kdebug_lck_attr);
	kdw_spin_lock = lck_spin_alloc_init(kdebug_lck_grp, kdebug_lck_attr);

	kd_ctrl_page.kdebug_flags |= KDBG_LOCKINIT;
}
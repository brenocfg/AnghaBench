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
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  int /*<<< orphan*/  lck_grp_attr_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  bstp_lock_attr ; 
 int /*<<< orphan*/  bstp_lock_grp ; 
 int /*<<< orphan*/  bstp_task_attr ; 
 int /*<<< orphan*/  bstp_task_grp ; 
 int /*<<< orphan*/  bstp_task_mtx ; 
 int /*<<< orphan*/  bstp_task_thread ; 
 scalar_t__ bstp_task_thread_func ; 
 int /*<<< orphan*/  kernel_thread_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_attr_setdebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_attr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bstp_create_task_thread(void)
{
	kern_return_t error;
	
	lck_grp_attr_t *lck_grp_attr = NULL;

	lck_grp_attr = lck_grp_attr_alloc_init();
	bstp_task_grp = lck_grp_alloc_init("bstp_task", lck_grp_attr);
	bstp_task_attr = lck_attr_alloc_init();
#if BRIDGE_DEBUG
	lck_attr_setdebug(bstp_task_attr);
#endif
	lck_mtx_init(bstp_task_mtx, bstp_lock_grp, bstp_lock_attr);
	lck_grp_attr_free(lck_grp_attr);

	error = kernel_thread_start((thread_continue_t)bstp_task_thread_func, NULL, &bstp_task_thread);
}
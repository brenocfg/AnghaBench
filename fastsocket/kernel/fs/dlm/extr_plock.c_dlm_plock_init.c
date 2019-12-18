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

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_print (char*,int) ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ops_lock ; 
 int /*<<< orphan*/  plock_dev_misc ; 
 int /*<<< orphan*/  recv_list ; 
 int /*<<< orphan*/  recv_wq ; 
 int /*<<< orphan*/  send_list ; 
 int /*<<< orphan*/  send_wq ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int dlm_plock_init(void)
{
	int rv;

	spin_lock_init(&ops_lock);
	INIT_LIST_HEAD(&send_list);
	INIT_LIST_HEAD(&recv_list);
	init_waitqueue_head(&send_wq);
	init_waitqueue_head(&recv_wq);

	rv = misc_register(&plock_dev_misc);
	if (rv)
		log_print("dlm_plock_init: misc_register failed %d", rv);
	return rv;
}
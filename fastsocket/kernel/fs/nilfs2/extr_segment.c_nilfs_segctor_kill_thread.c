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
struct nilfs_sc_info {int /*<<< orphan*/  sc_state_lock; int /*<<< orphan*/ * sc_task; int /*<<< orphan*/  sc_wait_task; int /*<<< orphan*/  sc_wait_daemon; int /*<<< orphan*/  sc_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_SEGCTOR_QUIT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_segctor_kill_thread(struct nilfs_sc_info *sci)
{
	sci->sc_state |= NILFS_SEGCTOR_QUIT;

	while (sci->sc_task) {
		wake_up(&sci->sc_wait_daemon);
		spin_unlock(&sci->sc_state_lock);
		wait_event(sci->sc_wait_task, sci->sc_task == NULL);
		spin_lock(&sci->sc_state_lock);
	}
}
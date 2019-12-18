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
struct iwl_notif_wait_data {int /*<<< orphan*/  notif_waitq; int /*<<< orphan*/  notif_waits; int /*<<< orphan*/  notif_wait_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void iwl_notification_wait_init(struct iwl_notif_wait_data *notif_wait)
{
	spin_lock_init(&notif_wait->notif_wait_lock);
	INIT_LIST_HEAD(&notif_wait->notif_waits);
	init_waitqueue_head(&notif_wait->notif_waitq);
}
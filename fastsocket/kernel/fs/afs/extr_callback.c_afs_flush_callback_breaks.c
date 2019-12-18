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
struct afs_server {int /*<<< orphan*/  cb_break_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_callback_update_worker ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void afs_flush_callback_breaks(struct afs_server *server)
{
	cancel_delayed_work(&server->cb_break_work);
	queue_delayed_work(afs_callback_update_worker,
			   &server->cb_break_work, 0);
}
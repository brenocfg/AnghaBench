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
struct writequeue_entry {int users; scalar_t__ offset; scalar_t__ end; scalar_t__ len; struct connection* con; } ;
struct connection {int /*<<< orphan*/  writequeue_lock; int /*<<< orphan*/  swork; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_WRITE_PENDING ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_workqueue ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dlm_lowcomms_commit_buffer(void *mh)
{
	struct writequeue_entry *e = (struct writequeue_entry *)mh;
	struct connection *con = e->con;
	int users;

	spin_lock(&con->writequeue_lock);
	users = --e->users;
	if (users)
		goto out;
	e->len = e->end - e->offset;
	spin_unlock(&con->writequeue_lock);

	if (!test_and_set_bit(CF_WRITE_PENDING, &con->flags)) {
		queue_work(send_workqueue, &con->swork);
	}
	return;

out:
	spin_unlock(&con->writequeue_lock);
	return;
}
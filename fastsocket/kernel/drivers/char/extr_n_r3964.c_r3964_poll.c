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
struct tty_struct {struct r3964_info* disc_data; } ;
struct r3964_message {int dummy; } ;
struct r3964_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  read_wait; } ;
struct r3964_client_info {struct r3964_message* first_msg; } ;
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  TRACE_L (char*) ; 
 int /*<<< orphan*/  current ; 
 struct r3964_client_info* findClient (struct r3964_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int r3964_poll(struct tty_struct *tty, struct file *file,
			struct poll_table_struct *wait)
{
	struct r3964_info *pInfo = tty->disc_data;
	struct r3964_client_info *pClient;
	struct r3964_message *pMsg = NULL;
	unsigned long flags;
	int result = POLLOUT;

	TRACE_L("POLL");

	pClient = findClient(pInfo, task_pid(current));
	if (pClient) {
		poll_wait(file, &pInfo->read_wait, wait);
		spin_lock_irqsave(&pInfo->lock, flags);
		pMsg = pClient->first_msg;
		spin_unlock_irqrestore(&pInfo->lock, flags);
		if (pMsg)
			result |= POLLIN | POLLRDNORM;
	} else {
		result = -EINVAL;
	}
	return result;
}
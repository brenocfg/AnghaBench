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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  harddog_in_fd ; 
 int /*<<< orphan*/  harddog_out_fd ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  lock_kernel () ; 
 char* mconsole_notify_socket () ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int start_watchdog (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int timer_alive ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int harddog_open(struct inode *inode, struct file *file)
{
	int err = -EBUSY;
	char *sock = NULL;

	lock_kernel();
	spin_lock(&lock);
	if(timer_alive)
		goto err;
#ifdef CONFIG_WATCHDOG_NOWAYOUT
	__module_get(THIS_MODULE);
#endif

#ifdef CONFIG_MCONSOLE
	sock = mconsole_notify_socket();
#endif
	err = start_watchdog(&harddog_in_fd, &harddog_out_fd, sock);
	if(err)
		goto err;

	timer_alive = 1;
	spin_unlock(&lock);
	unlock_kernel();
	return nonseekable_open(inode, file);
err:
	spin_unlock(&lock);
	unlock_kernel();
	return err;
}
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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 scalar_t__ apei_check_mce () ; 
 int /*<<< orphan*/  mce_apei_read_done ; 
 int /*<<< orphan*/  mce_wait ; 
 TYPE_1__ mcelog ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int mce_poll(struct file *file, poll_table *wait)
{
	poll_wait(file, &mce_wait, wait);
	if (rcu_dereference(mcelog.next))
		return POLLIN | POLLRDNORM;
	if (!mce_apei_read_done && apei_check_mce())
		return POLLIN | POLLRDNORM;
	return 0;
}
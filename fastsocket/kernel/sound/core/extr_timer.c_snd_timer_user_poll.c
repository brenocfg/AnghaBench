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
struct snd_timer_user {scalar_t__ qused; int /*<<< orphan*/  qchange_sleep; } ;
struct file {struct snd_timer_user* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int snd_timer_user_poll(struct file *file, poll_table * wait)
{
        unsigned int mask;
        struct snd_timer_user *tu;

        tu = file->private_data;

        poll_wait(file, &tu->qchange_sleep, wait);

	mask = 0;
	if (tu->qused)
		mask |= POLLIN | POLLRDNORM;

	return mask;
}
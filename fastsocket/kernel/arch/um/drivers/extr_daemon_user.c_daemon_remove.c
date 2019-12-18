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
struct daemon_data {int fd; int control; int /*<<< orphan*/ * local_addr; int /*<<< orphan*/ * ctl_addr; int /*<<< orphan*/ * data_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void daemon_remove(void *data)
{
	struct daemon_data *pri = data;

	close(pri->fd);
	pri->fd = -1;
	close(pri->control);
	pri->control = -1;

	kfree(pri->data_addr);
	pri->data_addr = NULL;
	kfree(pri->ctl_addr);
	pri->ctl_addr = NULL;
	kfree(pri->local_addr);
	pri->local_addr = NULL;
}
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
struct file {int /*<<< orphan*/  private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_2__ {scalar_t__ aborted; int /*<<< orphan*/  read_wait; } ;
typedef  TYPE_1__ diva_um_idi_os_context_t ;

/* Variables and functions */
 unsigned int POLLERR ; 
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 scalar_t__ diva_um_id_get_os_context (int /*<<< orphan*/ ) ; 
 int diva_user_mode_idi_ind_ready (int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int um_idi_poll(struct file *file, poll_table * wait)
{
	diva_um_idi_os_context_t *p_os;

	if (!file->private_data) {
		return (POLLERR);
	}

	if ((!(p_os =
	       (diva_um_idi_os_context_t *)
	       diva_um_id_get_os_context(file->private_data)))
	    || p_os->aborted) {
		return (POLLERR);
	}

	poll_wait(file, &p_os->read_wait, wait);

	if (p_os->aborted) {
		return (POLLERR);
	}

	switch (diva_user_mode_idi_ind_ready(file->private_data, file)) {
	case (-1):
		return (POLLERR);

	case 0:
		return (0);
	}

	return (POLLIN | POLLRDNORM);
}
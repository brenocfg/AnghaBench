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
struct tty_struct {struct acm* driver_data; } ;
struct file {int dummy; } ;
struct acm {int /*<<< orphan*/  port; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  acm_port_down (struct acm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acm_tty_unregister (struct acm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_mutex ; 
 int /*<<< orphan*/  tty_port_close_end (int /*<<< orphan*/ *,struct tty_struct*) ; 
 scalar_t__ tty_port_close_start (int /*<<< orphan*/ *,struct tty_struct*,struct file*) ; 
 int /*<<< orphan*/  tty_port_tty_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acm_tty_close(struct tty_struct *tty, struct file *filp)
{
	struct acm *acm = tty->driver_data;

	/* Perform the closing process and see if we need to do the hardware
	   shutdown */
	if (!acm)
		return;
	if (tty_port_close_start(&acm->port, tty, filp) == 0) {
		mutex_lock(&open_mutex);
		if (!acm->dev) {
			tty_port_tty_set(&acm->port, NULL);
			acm_tty_unregister(acm);
			tty->driver_data = NULL;
		}
		mutex_unlock(&open_mutex);
		return;
	}
	acm_port_down(acm, 0);
	tty_port_close_end(&acm->port, tty);
	tty_port_tty_set(&acm->port, NULL);
}
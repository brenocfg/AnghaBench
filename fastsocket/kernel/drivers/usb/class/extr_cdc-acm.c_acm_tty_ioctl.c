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
struct acm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACM_READY (struct acm*) ; 
 int EINVAL ; 
 int ENOIOCTLCMD ; 

__attribute__((used)) static int acm_tty_ioctl(struct tty_struct *tty, struct file *file,
					unsigned int cmd, unsigned long arg)
{
	struct acm *acm = tty->driver_data;

	if (!ACM_READY(acm))
		return -EINVAL;

	return -ENOIOCTLCMD;
}
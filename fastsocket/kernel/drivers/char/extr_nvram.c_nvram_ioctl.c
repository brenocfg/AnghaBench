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
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int ENOTTY ; 
 int NVRAM_BYTES ; 
#define  NVRAM_INIT 129 
#define  NVRAM_SETCKS 128 
 int /*<<< orphan*/  __nvram_set_checksum () ; 
 int /*<<< orphan*/  __nvram_write_byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvram_ioctl(struct inode *inode, struct file *file,
					unsigned int cmd, unsigned long arg)
{
	int i;

	switch (cmd) {

	case NVRAM_INIT:
		/* initialize NVRAM contents and checksum */
		if (!capable(CAP_SYS_ADMIN))
			return -EACCES;

		spin_lock_irq(&rtc_lock);

		for (i = 0; i < NVRAM_BYTES; ++i)
			__nvram_write_byte(0, i);
		__nvram_set_checksum();

		spin_unlock_irq(&rtc_lock);
		return 0;

	case NVRAM_SETCKS:
		/* just set checksum, contents unchanged (maybe useful after
		 * checksum garbaged somehow...) */
		if (!capable(CAP_SYS_ADMIN))
			return -EACCES;

		spin_lock_irq(&rtc_lock);
		__nvram_set_checksum();
		spin_unlock_irq(&rtc_lock);
		return 0;

	default:
		return -ENOTTY;
	}
}
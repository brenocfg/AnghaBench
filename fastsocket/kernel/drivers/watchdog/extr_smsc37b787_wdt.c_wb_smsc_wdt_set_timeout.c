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

/* Variables and functions */
 int /*<<< orphan*/  IODEV_NO ; 
 int /*<<< orphan*/  close_io_config () ; 
 int /*<<< orphan*/  io_lock ; 
 int /*<<< orphan*/  open_io_config () ; 
 int /*<<< orphan*/  select_io_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_timeout_value (unsigned char) ; 
 int /*<<< orphan*/  wdt_timer_ctrl (int) ; 

__attribute__((used)) static void wb_smsc_wdt_set_timeout(unsigned char new_timeout)
{
	spin_lock(&io_lock);
	open_io_config();
	select_io_device(IODEV_NO);

	/* set Power LED to blink, if we enable the timeout */
	wdt_timer_ctrl((new_timeout == 0) ? 0x00 : 0x02);

	/* set timeout value */
	wdt_timeout_value(new_timeout);

	close_io_config();
	spin_unlock(&io_lock);
}
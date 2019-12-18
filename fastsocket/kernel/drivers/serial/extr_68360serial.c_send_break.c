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
typedef  int /*<<< orphan*/  ser_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  begin_break (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_break (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  msleep_interruptible (unsigned int) ; 
 int /*<<< orphan*/  printk (char*,unsigned int,...) ; 

__attribute__((used)) static void send_break(ser_info_t *info, unsigned int duration)
{
#ifdef SERIAL_DEBUG_SEND_BREAK
	printk("rs_send_break(%d) jiff=%lu...", duration, jiffies);
#endif
	begin_break(info);
	msleep_interruptible(duration);
	end_break(info);
#ifdef SERIAL_DEBUG_SEND_BREAK
	printk("done jiffies=%lu\n", jiffies);
#endif
}
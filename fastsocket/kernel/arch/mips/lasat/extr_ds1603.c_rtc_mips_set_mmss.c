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
 int /*<<< orphan*/  SET_TIME_CMD ; 
 int /*<<< orphan*/  rtc_end_op () ; 
 int /*<<< orphan*/  rtc_init_op () ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  rtc_write_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_write_word (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int rtc_mips_set_mmss(unsigned long time)
{
	unsigned long flags;

	spin_lock_irqsave(&rtc_lock, flags);
	rtc_init_op();
	rtc_write_byte(SET_TIME_CMD);
	rtc_write_word(time);
	rtc_end_op();
	spin_unlock_irqrestore(&rtc_lock, flags);

	return 0;
}
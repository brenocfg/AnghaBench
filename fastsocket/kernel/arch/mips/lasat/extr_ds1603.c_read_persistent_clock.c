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
struct timespec {unsigned long tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_TIME_CMD ; 
 int /*<<< orphan*/  rtc_end_op () ; 
 int /*<<< orphan*/  rtc_init_op () ; 
 int /*<<< orphan*/  rtc_lock ; 
 unsigned long rtc_read_word () ; 
 int /*<<< orphan*/  rtc_write_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void read_persistent_clock(struct timespec *ts)
{
	unsigned long word;
	unsigned long flags;

	spin_lock_irqsave(&rtc_lock, flags);
	rtc_init_op();
	rtc_write_byte(READ_TIME_CMD);
	word = rtc_read_word();
	rtc_end_op();
	spin_unlock_irqrestore(&rtc_lock, flags);

	ts->tv_sec = word;
	ts->tv_nsec = 0;
}
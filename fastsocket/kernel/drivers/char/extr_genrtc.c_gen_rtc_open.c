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
 int EBUSY ; 
 int RTC_IS_OPEN ; 
 scalar_t__ gen_rtc_irq_data ; 
 int gen_rtc_status ; 
 scalar_t__ irq_active ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int gen_rtc_open(struct inode *inode, struct file *file)
{
	lock_kernel();
	if (gen_rtc_status & RTC_IS_OPEN) {
		unlock_kernel();
		return -EBUSY;
	}

	gen_rtc_status |= RTC_IS_OPEN;
	gen_rtc_irq_data = 0;
	irq_active = 0;
	unlock_kernel();

	return 0;
}
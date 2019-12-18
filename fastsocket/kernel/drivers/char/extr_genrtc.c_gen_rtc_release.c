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
 int RTC_AIE ; 
 int /*<<< orphan*/  RTC_IS_OPEN ; 
 int RTC_PIE ; 
 int RTC_UIE ; 
 int /*<<< orphan*/  gen_clear_rtc_irq_bit (int) ; 
 int /*<<< orphan*/  gen_rtc_status ; 

__attribute__((used)) static int gen_rtc_release(struct inode *inode, struct file *file)
{
	/*
	 * Turn off all interrupts once the device is no longer
	 * in use and clear the data.
	 */

	gen_clear_rtc_irq_bit(RTC_PIE|RTC_AIE|RTC_UIE);

	gen_rtc_status &= ~RTC_IS_OPEN;
	return 0;
}
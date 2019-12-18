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
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ S3C2410_TICNT ; 
 unsigned int S3C2410_TICNT_ENABLE ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 unsigned int readb (scalar_t__) ; 
 scalar_t__ s3c_rtc_base ; 
 int /*<<< orphan*/  s3c_rtc_pie_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int s3c_rtc_setfreq(struct device *dev, int freq)
{
	unsigned int tmp;

	if (!is_power_of_2(freq))
		return -EINVAL;

	spin_lock_irq(&s3c_rtc_pie_lock);

	tmp = readb(s3c_rtc_base + S3C2410_TICNT) & S3C2410_TICNT_ENABLE;
	tmp |= (128 / freq)-1;

	writeb(tmp, s3c_rtc_base + S3C2410_TICNT);
	spin_unlock_irq(&s3c_rtc_pie_lock);

	return 0;
}
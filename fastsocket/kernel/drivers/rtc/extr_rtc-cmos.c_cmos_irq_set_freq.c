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
struct cmos_rtc {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMOS_WRITE (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  RTC_FREQ_SELECT ; 
 int RTC_REF_CLCK_32KHZ ; 
 struct cmos_rtc* dev_get_drvdata (struct device*) ; 
 int ffs (int) ; 
 int /*<<< orphan*/  hpet_set_periodic_freq (int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  is_valid_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cmos_irq_set_freq(struct device *dev, int freq)
{
	struct cmos_rtc	*cmos = dev_get_drvdata(dev);
	int		f;
	unsigned long	flags;

	if (!is_valid_irq(cmos->irq))
		return -ENXIO;

	if (!is_power_of_2(freq))
		return -EINVAL;
	/* 0 = no irqs; 1 = 2^15 Hz ... 15 = 2^0 Hz */
	f = ffs(freq);
	if (f-- > 16)
		return -EINVAL;
	f = 16 - f;

	spin_lock_irqsave(&rtc_lock, flags);
	hpet_set_periodic_freq(freq);
	CMOS_WRITE(RTC_REF_CLCK_32KHZ | f, RTC_FREQ_SELECT);
	spin_unlock_irqrestore(&rtc_lock, flags);

	return 0;
}
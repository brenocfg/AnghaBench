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
 int /*<<< orphan*/  ECMPHREG ; 
 int /*<<< orphan*/  ECMPLREG ; 
 int /*<<< orphan*/  ECMPMREG ; 
 int /*<<< orphan*/  RTCL1HREG ; 
 int /*<<< orphan*/  RTCL1LREG ; 
 int /*<<< orphan*/  aie_irq ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pie_irq ; 
 int /*<<< orphan*/  rtc1_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vr41xx_rtc_release(struct device *dev)
{

	spin_lock_irq(&rtc_lock);

	rtc1_write(ECMPLREG, 0);
	rtc1_write(ECMPMREG, 0);
	rtc1_write(ECMPHREG, 0);
	rtc1_write(RTCL1LREG, 0);
	rtc1_write(RTCL1HREG, 0);

	spin_unlock_irq(&rtc_lock);

	disable_irq(aie_irq);
	disable_irq(pie_irq);
}
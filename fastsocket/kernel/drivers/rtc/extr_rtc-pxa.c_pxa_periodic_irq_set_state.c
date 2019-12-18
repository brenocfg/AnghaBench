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
struct pxa_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int RTSR_PIALE ; 
 int RTSR_PICE ; 
 struct pxa_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtsr_clear_bits (struct pxa_rtc*,int) ; 
 int /*<<< orphan*/  rtsr_set_bits (struct pxa_rtc*,int) ; 

__attribute__((used)) static int pxa_periodic_irq_set_state(struct device *dev, int enabled)
{
	struct pxa_rtc *pxa_rtc = dev_get_drvdata(dev);

	if (enabled)
		rtsr_set_bits(pxa_rtc, RTSR_PIALE | RTSR_PICE);
	else
		rtsr_clear_bits(pxa_rtc, RTSR_PIALE | RTSR_PICE);

	return 0;
}
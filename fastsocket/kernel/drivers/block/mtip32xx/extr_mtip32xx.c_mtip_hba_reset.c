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
struct driver_data {scalar_t__ mmio; int /*<<< orphan*/  dd_flag; } ;

/* Variables and functions */
 scalar_t__ HOST_CTL ; 
 int HOST_RESET ; 
 int /*<<< orphan*/  MTIP_DDF_REMOVE_PENDING_BIT ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mdelay (int) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int readl (scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtip_hba_reset(struct driver_data *dd)
{
	unsigned long timeout;

	/* Set the reset bit */
	writel(HOST_RESET, dd->mmio + HOST_CTL);

	/* Flush */
	readl(dd->mmio + HOST_CTL);

	/* Spin for up to 2 seconds, waiting for reset acknowledgement */
	timeout = jiffies + msecs_to_jiffies(2000);
	do {
		mdelay(10);
		if (test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &dd->dd_flag))
			return -1;

	} while ((readl(dd->mmio + HOST_CTL) & HOST_RESET)
		 && time_before(jiffies, timeout));

	if (readl(dd->mmio + HOST_CTL) & HOST_RESET)
		return -1;

	return 0;
}
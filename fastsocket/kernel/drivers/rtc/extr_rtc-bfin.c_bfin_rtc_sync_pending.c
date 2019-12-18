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
 int HZ ; 
 int RTC_ISTAT_WRITE_PENDING ; 
 int bfin_read_RTC_ISTAT () ; 
 int /*<<< orphan*/  bfin_write_complete ; 
 int /*<<< orphan*/  dev_dbg_stamp (struct device*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void bfin_rtc_sync_pending(struct device *dev)
{
	dev_dbg_stamp(dev);
	while (bfin_read_RTC_ISTAT() & RTC_ISTAT_WRITE_PENDING)
		wait_for_completion_timeout(&bfin_write_complete, HZ * 5);
	dev_dbg_stamp(dev);
}
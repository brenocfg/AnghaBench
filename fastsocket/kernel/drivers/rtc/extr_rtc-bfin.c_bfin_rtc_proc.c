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
typedef  int u16 ;
struct seq_file {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int RTC_ISTAT_ALARM ; 
 int RTC_ISTAT_ALARM_DAY ; 
 int RTC_ISTAT_SEC ; 
 int bfin_read_RTC_ICTL () ; 
 int /*<<< orphan*/  dev_dbg_stamp (struct device*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (int) ; 

__attribute__((used)) static int bfin_rtc_proc(struct device *dev, struct seq_file *seq)
{
#define yesno(x) ((x) ? "yes" : "no")
	u16 ictl = bfin_read_RTC_ICTL();
	dev_dbg_stamp(dev);
	seq_printf(seq,
		"alarm_IRQ\t: %s\n"
		"wkalarm_IRQ\t: %s\n"
		"seconds_IRQ\t: %s\n",
		yesno(ictl & RTC_ISTAT_ALARM),
		yesno(ictl & RTC_ISTAT_ALARM_DAY),
		yesno(ictl & RTC_ISTAT_SEC));
	return 0;
#undef yesno
}
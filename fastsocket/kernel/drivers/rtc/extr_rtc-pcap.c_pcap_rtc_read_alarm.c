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
typedef  unsigned long u32 ;
struct rtc_time {int dummy; } ;
struct rtc_wkalrm {struct rtc_time time; } ;
struct platform_device {int dummy; } ;
struct pcap_rtc {int /*<<< orphan*/  pcap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_REG_RTC_DAYA ; 
 int /*<<< orphan*/  PCAP_REG_RTC_TODA ; 
 unsigned long PCAP_RTC_DAY_MASK ; 
 unsigned long PCAP_RTC_TOD_MASK ; 
 unsigned long SEC_PER_DAY ; 
 int /*<<< orphan*/  ezx_pcap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 struct pcap_rtc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,struct rtc_time*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int pcap_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct pcap_rtc *pcap_rtc = platform_get_drvdata(pdev);
	struct rtc_time *tm = &alrm->time;
	unsigned long secs;
	u32 tod;	/* time of day, seconds since midnight */
	u32 days;	/* days since 1/1/1970 */

	ezx_pcap_read(pcap_rtc->pcap, PCAP_REG_RTC_TODA, &tod);
	secs = tod & PCAP_RTC_TOD_MASK;

	ezx_pcap_read(pcap_rtc->pcap, PCAP_REG_RTC_DAYA, &days);
	secs += (days & PCAP_RTC_DAY_MASK) * SEC_PER_DAY;

	rtc_time_to_tm(secs, tm);

	return 0;
}
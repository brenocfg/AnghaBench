#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; scalar_t__ tm_wday; } ;
struct TYPE_2__ {int adb_type; } ;

/* Variables and functions */
#define  MAC_ADB_CUDA 133 
#define  MAC_ADB_II 132 
#define  MAC_ADB_IISI 131 
#define  MAC_ADB_IOP 130 
#define  MAC_ADB_PB1 129 
#define  MAC_ADB_PB2 128 
 unsigned long cuda_read_time () ; 
 int /*<<< orphan*/  cuda_write_time (unsigned long) ; 
 unsigned long maciisi_read_time () ; 
 int /*<<< orphan*/  maciisi_write_time (unsigned long) ; 
 TYPE_1__* macintosh_config ; 
 unsigned long mktime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long pmu_read_time () ; 
 int /*<<< orphan*/  pmu_write_time (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmktime (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long via_read_time () ; 
 int /*<<< orphan*/  via_write_time (unsigned long) ; 

int mac_hwclk(int op, struct rtc_time *t)
{
	unsigned long now;

	if (!op) { /* read */
		switch (macintosh_config->adb_type) {
		case MAC_ADB_II:
		case MAC_ADB_IOP:
			now = via_read_time();
			break;
		case MAC_ADB_IISI:
			now = maciisi_read_time();
			break;
		case MAC_ADB_PB1:
		case MAC_ADB_PB2:
			now = pmu_read_time();
			break;
		case MAC_ADB_CUDA:
			now = cuda_read_time();
			break;
		default:
			now = 0;
		}

		t->tm_wday = 0;
		unmktime(now, 0,
			 &t->tm_year, &t->tm_mon, &t->tm_mday,
			 &t->tm_hour, &t->tm_min, &t->tm_sec);
#if 0
		printk("mac_hwclk: read %04d-%02d-%-2d %02d:%02d:%02d\n",
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
			t->tm_hour, t->tm_min, t->tm_sec);
#endif
	} else { /* write */
#if 0
		printk("mac_hwclk: tried to write %04d-%02d-%-2d %02d:%02d:%02d\n",
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
			t->tm_hour, t->tm_min, t->tm_sec);
#endif

		now = mktime(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
			     t->tm_hour, t->tm_min, t->tm_sec);

		switch (macintosh_config->adb_type) {
		case MAC_ADB_II:
		case MAC_ADB_IOP:
			via_write_time(now);
			break;
		case MAC_ADB_CUDA:
			cuda_write_time(now);
			break;
		case MAC_ADB_PB1:
		case MAC_ADB_PB2:
			pmu_write_time(now);
			break;
		case MAC_ADB_IISI:
			maciisi_write_time(now);
		}
	}
	return 0;
}
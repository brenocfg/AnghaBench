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
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 long RTC_OFFSET ; 
 int /*<<< orphan*/  printk (char*,long,long) ; 
 int /*<<< orphan*/  via_pram_command (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long via_read_time(void)
{
	union {
		__u8  cdata[4];
		long  idata;
	} result, last_result;
	int	ct;

	/*
	 * The NetBSD guys say to loop until you get the same reading
	 * twice in a row.
	 */

	ct = 0;
	do {
		if (++ct > 10) {
			printk("via_read_time: couldn't get valid time, "
			       "last read = 0x%08lx and 0x%08lx\n",
			       last_result.idata, result.idata);
			break;
		}

		last_result.idata = result.idata;
		result.idata = 0;

		via_pram_command(0x81, &result.cdata[3]);
		via_pram_command(0x85, &result.cdata[2]);
		via_pram_command(0x89, &result.cdata[1]);
		via_pram_command(0x8D, &result.cdata[0]);
	} while (result.idata != last_result.idata);

	return result.idata - RTC_OFFSET;
}
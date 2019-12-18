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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  src ;
typedef  int hrtime_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_pfargd_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int NANOSEC ; 
 int /*<<< orphan*/  ctime_r (int /*<<< orphan*/ *,char*,...) ; 
 int dt_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char*) ; 

__attribute__((used)) static int
pfprint_time(dtrace_hdl_t *dtp, FILE *fp, const char *format,
    const dt_pfargd_t *pfd, const void *addr, size_t size, uint64_t normal)
{
	char src[32], buf[32], *dst = buf;
	hrtime_t time = *((uint64_t *)addr);
	time_t sec = (time_t)(time / NANOSEC);
	int i;

	/*
	 * ctime(3C) returns a string of the form "Dec  3 17:20:00 1973\n\0".
	 * Below, we turn this into the canonical adb/mdb /[yY] format,
	 * "1973 Dec  3 17:20:00".
	 */
#ifdef illumos
	(void) ctime_r(&sec, src, sizeof (src));
#else
	(void) ctime_r(&sec, src);
#endif

	/*
	 * Place the 4-digit year at the head of the string...
	 */
	for (i = 20; i < 24; i++)
		*dst++ = src[i];

	/*
	 * ...and follow it with the remainder (month, day, hh:mm:ss).
	 */
	for (i = 3; i < 19; i++)
		*dst++ = src[i];

	*dst = '\0';
	return (dt_printf(dtp, fp, format, buf));
}
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
typedef  unsigned long uint64_t ;

/* Variables and functions */
 unsigned long MSEC2NSEC (unsigned long) ; 
 int sscanf (char*,char*,unsigned long*,unsigned long*) ; 

__attribute__((used)) static int
parse_delay(char *str, uint64_t *delay, uint64_t *nlanes)
{
	unsigned long scan_delay;
	unsigned long scan_nlanes;

	if (sscanf(str, "%lu:%lu", &scan_delay, &scan_nlanes) != 2)
		return (1);

	/*
	 * We explicitly disallow a delay of zero here, because we key
	 * off this value being non-zero in translate_device(), to
	 * determine if the fault is a ZINJECT_DELAY_IO fault or not.
	 */
	if (scan_delay == 0)
		return (1);

	/*
	 * The units for the CLI delay parameter is milliseconds, but
	 * the data passed to the kernel is interpreted as nanoseconds.
	 * Thus we scale the milliseconds to nanoseconds here, and this
	 * nanosecond value is used to pass the delay to the kernel.
	 */
	*delay = MSEC2NSEC(scan_delay);
	*nlanes = scan_nlanes;

	return (0);
}
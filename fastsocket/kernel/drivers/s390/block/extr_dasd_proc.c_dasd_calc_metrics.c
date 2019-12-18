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
typedef  int off_t ;

/* Variables and functions */

__attribute__((used)) static int
dasd_calc_metrics(char *page, char **start, off_t off,
		  int count, int *eof, int len)
{
	len = (len > off) ? len - off : 0;
	if (len > count)
		len = count;
	if (len < count)
		*eof = 1;
	*start = page + off;
	return len;
}
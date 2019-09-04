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
typedef  int /*<<< orphan*/  kd_buf ;

/* Variables and functions */
 unsigned int nkdbufs ; 
 int sane_size ; 

__attribute__((used)) static void
kdbg_set_nkdbufs(unsigned int value)
{
	/*
	 * We allow a maximum buffer size of 50% of either ram or max mapped
	 * address, whichever is smaller 'value' is the desired number of trace
	 * entries
	 */
	unsigned int max_entries = (sane_size / 2) / sizeof(kd_buf);

	if (value <= max_entries) {
		nkdbufs = value;
	} else {
		nkdbufs = max_entries;
	}
}
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

/* Variables and functions */
 int TEST_MTX_MAX_STATS ; 
 int /*<<< orphan*/  erase_test_mtx_stats (int) ; 

void
erase_all_test_mtx_stats(void)
{
	int i;
	for (i = 0; i < TEST_MTX_MAX_STATS; i++) {
		erase_test_mtx_stats(i);
	}
}
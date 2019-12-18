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
 int /*<<< orphan*/  FINISH_FLUSH ; 
 int /*<<< orphan*/  flush_range (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  init_mm ; 

void flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	flush_range(&init_mm, start, end);
	FINISH_FLUSH;
}
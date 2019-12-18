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
 int DCSR (int) ; 
 int DCSR_STOPSTATE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int loops_per_jiffy ; 

__attribute__((used)) static int wait_dma_channel_stop(int channel)
{
	unsigned long limit = loops_per_jiffy << 1;

	while (!(DCSR(channel) & DCSR_STOPSTATE) && --limit)
		cpu_relax();

	return limit;
}
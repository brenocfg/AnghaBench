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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  HSTIM_COUNTER ; 
 int /*<<< orphan*/  HSTIM_MATCH0 ; 
 int LATCH ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int tick_nsec ; 

__attribute__((used)) static unsigned long pnx4008_gettimeoffset(void)
{
	u32 ticks_to_match =
	    __raw_readl(HSTIM_MATCH0) - __raw_readl(HSTIM_COUNTER);
	u32 elapsed = LATCH - ticks_to_match;
	return (elapsed * (tick_nsec / 1000)) / LATCH;
}
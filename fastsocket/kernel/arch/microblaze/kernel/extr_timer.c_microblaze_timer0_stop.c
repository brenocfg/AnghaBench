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
 scalar_t__ TCSR0 ; 
 int TCSR_ENT ; 
 scalar_t__ TIMER_BASE ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int) ; 

__attribute__((used)) static inline void microblaze_timer0_stop(void)
{
	out_be32(TIMER_BASE + TCSR0, in_be32(TIMER_BASE + TCSR0) & ~TCSR_ENT);
}
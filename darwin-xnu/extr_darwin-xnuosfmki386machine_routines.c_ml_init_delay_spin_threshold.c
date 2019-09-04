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
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  delay_spin_threshold ; 
 int /*<<< orphan*/  nanoseconds_to_absolutetime (int,int /*<<< orphan*/ *) ; 

void
ml_init_delay_spin_threshold(int threshold_us)
{
	nanoseconds_to_absolutetime(threshold_us * NSEC_PER_USEC, &delay_spin_threshold);
}
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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 scalar_t__ atomic_load_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keep_going ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 scalar_t__ nanos_to_abs (scalar_t__) ; 

__attribute__((used)) static void
spin_for_duration(uint32_t seconds)
{
    uint64_t duration       = nanos_to_abs((uint64_t)seconds * NSEC_PER_SEC);
    uint64_t current_time   = mach_absolute_time();
    uint64_t timeout        = duration + current_time;

    uint64_t spin_count = 0;

    while (mach_absolute_time() < timeout && atomic_load_explicit(&keep_going,
		memory_order_relaxed)) {
        spin_count++;
    }
}
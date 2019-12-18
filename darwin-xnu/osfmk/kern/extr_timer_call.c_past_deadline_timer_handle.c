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

/* Variables and functions */
 int /*<<< orphan*/  past_deadline_deltas ; 
 scalar_t__ past_deadline_longest ; 
 scalar_t__ past_deadline_shortest ; 
 scalar_t__ past_deadline_timer_adjustment ; 
 int /*<<< orphan*/  past_deadline_timers ; 

__attribute__((used)) static uint64_t
past_deadline_timer_handle(uint64_t deadline, uint64_t ctime)
{
    uint64_t delta = (ctime - deadline);
    
    past_deadline_timers++;
    past_deadline_deltas += delta;
    if (delta > past_deadline_longest)
	past_deadline_longest = deadline;
    if (delta < past_deadline_shortest)
	past_deadline_shortest = delta;

    return (ctime + past_deadline_timer_adjustment);
}
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
typedef  int /*<<< orphan*/  timer_t ;

/* Variables and functions */
 scalar_t__ timer_grab (int /*<<< orphan*/ ) ; 

uint64_t
timer_delta(timer_t timer, uint64_t *prev_in_cur_out)
{
	uint64_t old = *prev_in_cur_out;
	uint64_t new = *prev_in_cur_out = timer_grab(timer);
	return (new - old);
}
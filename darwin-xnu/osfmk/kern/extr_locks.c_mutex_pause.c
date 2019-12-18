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
typedef  scalar_t__ wait_result_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 size_t MAX_COLLISION ; 
 size_t MAX_COLLISION_COUNTS ; 
 int /*<<< orphan*/  NSEC_PER_USEC ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 scalar_t__ THREAD_TIMED_OUT ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 scalar_t__ THREAD_WAITING ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ assert_wait_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 size_t* collision_backoffs ; 
 int /*<<< orphan*/ * max_collision_count ; 
 scalar_t__ thread_block (int /*<<< orphan*/ ) ; 

void
mutex_pause(uint32_t collisions)
{
	wait_result_t wait_result;
	uint32_t	back_off;

	if (collisions >= MAX_COLLISION_COUNTS)
	        collisions = MAX_COLLISION_COUNTS - 1;
	max_collision_count[collisions]++;

	if (collisions >= MAX_COLLISION)
	        collisions = MAX_COLLISION - 1;
	back_off = collision_backoffs[collisions];

	wait_result = assert_wait_timeout((event_t)mutex_pause, THREAD_UNINT, back_off, NSEC_PER_USEC);
	assert(wait_result == THREAD_WAITING);

	wait_result = thread_block(THREAD_CONTINUE_NULL);
	assert(wait_result == THREAD_TIMED_OUT);
}
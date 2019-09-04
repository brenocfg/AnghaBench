#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_call_t ;
typedef  size_t thread_call_index_t ;
typedef  int /*<<< orphan*/ * thread_call_group_t ;
struct TYPE_3__ {size_t tc_index; } ;

/* Variables and functions */
 size_t THREAD_CALL_INDEX_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * thread_call_groups ; 

__attribute__((used)) static inline thread_call_group_t
thread_call_get_group(thread_call_t call)
{
	thread_call_index_t index = call->tc_index;

	assert(index >= 0 && index < THREAD_CALL_INDEX_MAX);

	return &thread_call_groups[index];
}
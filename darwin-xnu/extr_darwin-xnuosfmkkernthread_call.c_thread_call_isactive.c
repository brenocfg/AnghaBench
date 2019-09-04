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
typedef  int /*<<< orphan*/  spl_t ;
typedef  int boolean_t ;
struct TYPE_3__ {scalar_t__ tc_submit_count; scalar_t__ tc_finish_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_ints_and_lock () ; 
 int /*<<< orphan*/  enable_ints_and_unlock (int /*<<< orphan*/ ) ; 

boolean_t
thread_call_isactive(thread_call_t call) 
{
	boolean_t active;

	spl_t s = disable_ints_and_lock();
	active = (call->tc_submit_count > call->tc_finish_count);
	enable_ints_and_unlock(s);

	return active;
}
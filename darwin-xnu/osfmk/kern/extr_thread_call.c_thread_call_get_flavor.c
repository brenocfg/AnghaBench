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
typedef  int /*<<< orphan*/  thread_call_flavor_t ;
struct TYPE_3__ {int tc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCF_ABSOLUTE ; 
 int /*<<< orphan*/  TCF_CONTINUOUS ; 
 int THREAD_CALL_CONTINUOUS ; 

__attribute__((used)) static inline thread_call_flavor_t
thread_call_get_flavor(thread_call_t call)
{
	return (call->tc_flags & THREAD_CALL_CONTINUOUS) ? TCF_CONTINUOUS : TCF_ABSOLUTE;
}
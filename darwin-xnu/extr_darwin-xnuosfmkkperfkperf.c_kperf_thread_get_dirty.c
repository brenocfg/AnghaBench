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
typedef  TYPE_1__* thread_t ;
typedef  int boolean_t ;
struct TYPE_3__ {scalar_t__ c_switch; scalar_t__ kperf_c_switch; } ;

/* Variables and functions */

boolean_t
kperf_thread_get_dirty(thread_t thread)
{
	return (thread->c_switch != thread->kperf_c_switch);
}
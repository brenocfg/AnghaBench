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
struct TYPE_3__ {int /*<<< orphan*/  thread_handle; } ;
typedef  TYPE_1__ osi_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char const* pcTaskGetTaskName (int /*<<< orphan*/ ) ; 

const char *osi_thread_name(osi_thread_t *thread)
{
    assert(thread != NULL);

    return pcTaskGetTaskName(thread->thread_handle);
}
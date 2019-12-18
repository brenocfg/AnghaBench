#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int high_priority; } ;
typedef  TYPE_1__ CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  merge_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

void rpc_high_priority_begin(CLIENT_THREAD_STATE_T *thread)
{
   vcos_assert(!thread->high_priority);
   merge_flush(thread);
   thread->high_priority = true;
}
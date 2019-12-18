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
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  platform_mutex_release (int /*<<< orphan*/ *) ; 

void rpc_end(CLIENT_THREAD_STATE_T *thread)
{
   UNUSED(thread);
   platform_mutex_release(&mutex);
}
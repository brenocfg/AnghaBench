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
struct TYPE_4__ {int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ VCOS_THREAD_T ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  vcos_thread_cleanup (TYPE_1__*) ; 

void vcos_thread_join(VCOS_THREAD_T *thread,
                             void **pData)
{
   pthread_join(thread->thread, pData);
   vcos_thread_cleanup(thread);
}
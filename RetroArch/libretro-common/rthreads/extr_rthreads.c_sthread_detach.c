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
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ sthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int pthread_detach (int /*<<< orphan*/ ) ; 

int sthread_detach(sthread_t *thread)
{
#ifdef USE_WIN32_THREADS
   CloseHandle(thread->thread);
   free(thread);
   return 0;
#else
   return pthread_detach(thread->id);
#endif
}
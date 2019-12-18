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
struct TYPE_3__ {scalar_t__ dummy; } ;
typedef  TYPE_1__ VCOS_THREAD_T ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_exit (void*) ; 
 int /*<<< orphan*/  vcos_free (void*) ; 
 TYPE_1__* vcos_thread_current () ; 

void vcos_thread_exit(void *arg)
{
   VCOS_THREAD_T *thread = vcos_thread_current();

   if ( thread && thread->dummy )
   {
      vcos_free ( (void*) thread );
      thread = NULL;
   }

   pthread_exit(arg);
}
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
struct TYPE_4__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  cs; int /*<<< orphan*/  hot_potato; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ scond_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 

void scond_free(scond_t *cond)
{
   if (!cond)
      return;

#ifdef USE_WIN32_THREADS
   CloseHandle(cond->event);
   CloseHandle(cond->hot_potato);
   DeleteCriticalSection(&cond->cs);
#else
   pthread_cond_destroy(&cond->cond);
#endif
   free(cond);
}
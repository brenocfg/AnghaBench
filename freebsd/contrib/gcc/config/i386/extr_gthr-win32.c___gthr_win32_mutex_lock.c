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
struct TYPE_3__ {int /*<<< orphan*/  counter; int /*<<< orphan*/  sema; } ;
typedef  TYPE_1__ __gthread_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 scalar_t__ InterlockedIncrement (int /*<<< orphan*/ *) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
__gthr_win32_mutex_lock (__gthread_mutex_t *mutex)
{
  if (InterlockedIncrement (&mutex->counter) == 0 ||
      WaitForSingleObject (mutex->sema, INFINITE) == WAIT_OBJECT_0)
    return 0;
  else
    {
      /* WaitForSingleObject returns WAIT_FAILED, and we can only do
         some best-effort cleanup here.  */
      InterlockedDecrement (&mutex->counter);
      return 1;
    }
}
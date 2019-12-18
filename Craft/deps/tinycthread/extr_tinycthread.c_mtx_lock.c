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
struct TYPE_4__ {scalar_t__ mAlreadyLocked; int /*<<< orphan*/  mRecursive; int /*<<< orphan*/  mHandle; } ;
typedef  TYPE_1__ mtx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 scalar_t__ TRUE ; 
 scalar_t__ pthread_mutex_lock (TYPE_1__*) ; 
 int thrd_error ; 
 int thrd_success ; 

int mtx_lock(mtx_t *mtx)
{
#if defined(_TTHREAD_WIN32_)
  EnterCriticalSection(&mtx->mHandle);
  if (!mtx->mRecursive)
  {
    while(mtx->mAlreadyLocked) Sleep(1000); /* Simulate deadlock... */
    mtx->mAlreadyLocked = TRUE;
  }
  return thrd_success;
#else
  return pthread_mutex_lock(mtx) == 0 ? thrd_success : thrd_error;
#endif
}
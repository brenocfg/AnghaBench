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
struct TYPE_4__ {int /*<<< orphan*/  mHandle; scalar_t__ mAlreadyLocked; int /*<<< orphan*/  mRecursive; } ;
typedef  TYPE_1__ mtx_t ;

/* Variables and functions */
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ TryEnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_trylock (TYPE_1__*) ; 
 int thrd_busy ; 
 int thrd_success ; 

int mtx_trylock(mtx_t *mtx)
{
#if defined(_TTHREAD_WIN32_)
  int ret = TryEnterCriticalSection(&mtx->mHandle) ? thrd_success : thrd_busy;
  if ((!mtx->mRecursive) && (ret == thrd_success) && mtx->mAlreadyLocked)
  {
    LeaveCriticalSection(&mtx->mHandle);
    ret = thrd_busy;
  }
  return ret;
#else
  return (pthread_mutex_trylock(mtx) == 0) ? thrd_success : thrd_busy;
#endif
}
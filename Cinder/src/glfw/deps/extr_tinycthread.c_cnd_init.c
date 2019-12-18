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
struct TYPE_4__ {int /*<<< orphan*/ ** mEvents; int /*<<< orphan*/  mWaitersCountLock; scalar_t__ mWaitersCount; } ;
typedef  TYPE_1__ cnd_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 void* CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 size_t _CONDITION_EVENT_ALL ; 
 size_t _CONDITION_EVENT_ONE ; 
 scalar_t__ pthread_cond_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int thrd_error ; 
 int thrd_success ; 

int cnd_init(cnd_t *cond)
{
#if defined(_TTHREAD_WIN32_)
  cond->mWaitersCount = 0;

  /* Init critical section */
  InitializeCriticalSection(&cond->mWaitersCountLock);

  /* Init events */
  cond->mEvents[_CONDITION_EVENT_ONE] = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (cond->mEvents[_CONDITION_EVENT_ONE] == NULL)
  {
    cond->mEvents[_CONDITION_EVENT_ALL] = NULL;
    return thrd_error;
  }
  cond->mEvents[_CONDITION_EVENT_ALL] = CreateEvent(NULL, TRUE, FALSE, NULL);
  if (cond->mEvents[_CONDITION_EVENT_ALL] == NULL)
  {
    CloseHandle(cond->mEvents[_CONDITION_EVENT_ONE]);
    cond->mEvents[_CONDITION_EVENT_ONE] = NULL;
    return thrd_error;
  }

  return thrd_success;
#else
  return pthread_cond_init(cond, NULL) == 0 ? thrd_success : thrd_error;
#endif
}
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
struct TYPE_4__ {int /*<<< orphan*/  mWaitersCountLock; int /*<<< orphan*/ ** mEvents; } ;
typedef  TYPE_1__ cnd_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 size_t _CONDITION_EVENT_ALL ; 
 size_t _CONDITION_EVENT_ONE ; 
 int /*<<< orphan*/  pthread_cond_destroy (TYPE_1__*) ; 

void cnd_destroy(cnd_t *cond)
{
#if defined(_TTHREAD_WIN32_)
  if (cond->mEvents[_CONDITION_EVENT_ONE] != NULL)
  {
    CloseHandle(cond->mEvents[_CONDITION_EVENT_ONE]);
  }
  if (cond->mEvents[_CONDITION_EVENT_ALL] != NULL)
  {
    CloseHandle(cond->mEvents[_CONDITION_EVENT_ALL]);
  }
  DeleteCriticalSection(&cond->mWaitersCountLock);
#else
  pthread_cond_destroy(cond);
#endif
}
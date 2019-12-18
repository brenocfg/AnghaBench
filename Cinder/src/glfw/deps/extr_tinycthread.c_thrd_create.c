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
typedef  scalar_t__ thrd_t ;
typedef  int /*<<< orphan*/  thrd_start_t ;
struct TYPE_3__ {void* mArg; int /*<<< orphan*/  mFunction; } ;
typedef  TYPE_1__ _thread_start_info ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ _beginthreadex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _thrd_wrapper_function ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ pthread_create (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int thrd_error ; 
 int thrd_nomem ; 
 int thrd_success ; 

int thrd_create(thrd_t *thr, thrd_start_t func, void *arg)
{
  /* Fill out the thread startup information (passed to the thread wrapper,
     which will eventually free it) */
  _thread_start_info* ti = (_thread_start_info*)malloc(sizeof(_thread_start_info));
  if (ti == NULL)
  {
    return thrd_nomem;
  }
  ti->mFunction = func;
  ti->mArg = arg;

  /* Create the thread */
#if defined(_TTHREAD_WIN32_)
  *thr = (HANDLE)_beginthreadex(NULL, 0, _thrd_wrapper_function, (void *)ti, 0, NULL);
#elif defined(_TTHREAD_POSIX_)
  if(pthread_create(thr, NULL, _thrd_wrapper_function, (void *)ti) != 0)
  {
    *thr = 0;
  }
#endif

  /* Did we fail to create the thread? */
  if(!*thr)
  {
    free(ti);
    return thrd_error;
  }

  return thrd_success;
}
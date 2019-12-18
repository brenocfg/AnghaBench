#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  thrd_t ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetExitCodeThread (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ WAIT_FAILED ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int thrd_error ; 
 int thrd_success ; 

int thrd_join(thrd_t thr, int *res)
{
#if defined(_TTHREAD_WIN32_)
  if (WaitForSingleObject(thr, INFINITE) == WAIT_FAILED)
  {
    return thrd_error;
  }
  if (res != NULL)
  {
    DWORD dwRes;
    GetExitCodeThread(thr, &dwRes);
    *res = dwRes;
  }
#elif defined(_TTHREAD_POSIX_)
  void *pres;
  int ires = 0;
  if (pthread_join(thr, &pres) != 0)
  {
    return thrd_error;
  }
  if (pres != NULL)
  {
    ires = *(int*)pres;
    free(pres);
  }
  if (res != NULL)
  {
    *res = ires;
  }
#endif
  return thrd_success;
}
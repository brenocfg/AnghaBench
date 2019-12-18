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
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_SIZEPTR ;
typedef  scalar_t__ PTW32_INTERLOCKED_SIZE ;
typedef  scalar_t__ PTW32_INTERLOCKED_LONG ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  PTW32_FALSE ; 
 scalar_t__ PTW32_INTERLOCKED_COMPARE_EXCHANGE_SIZE (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ PTW32_INTERLOCKED_EXCHANGE_ADD_SIZE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WaitForSingleObject (scalar_t__,int /*<<< orphan*/ ) ; 

void 
ptw32_mcs_flag_wait (HANDLE * flag)
{
  if ((PTW32_INTERLOCKED_LONG)0 ==
        PTW32_INTERLOCKED_EXCHANGE_ADD_SIZE((PTW32_INTERLOCKED_SIZEPTR)flag,
                                            (PTW32_INTERLOCKED_SIZE)0)) /* MBR fence */
    {
      /* the flag is not set. create event. */

      HANDLE e = CreateEvent(NULL, PTW32_FALSE, PTW32_FALSE, NULL);

      if ((PTW32_INTERLOCKED_SIZE)0 == PTW32_INTERLOCKED_COMPARE_EXCHANGE_SIZE(
			                  (PTW32_INTERLOCKED_SIZEPTR)flag,
			                  (PTW32_INTERLOCKED_SIZE)e,
			                  (PTW32_INTERLOCKED_SIZE)0))
	{
	  /* stored handle in the flag. wait on it now. */
	  WaitForSingleObject(e, INFINITE);
	}

      CloseHandle(e);
    }
}
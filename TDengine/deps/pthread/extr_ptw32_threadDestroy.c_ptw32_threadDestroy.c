#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  threadCopy ;
struct TYPE_7__ {int /*<<< orphan*/ * threadH; int /*<<< orphan*/ * cancelEvent; } ;
typedef  TYPE_1__ ptw32_thread_t ;
struct TYPE_8__ {scalar_t__ p; } ;
typedef  TYPE_2__ pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ptw32_threadReusePush (TYPE_2__) ; 

void
ptw32_threadDestroy (pthread_t thread)
{
  ptw32_thread_t * tp = (ptw32_thread_t *) thread.p;
  ptw32_thread_t threadCopy;

  if (tp != NULL)
    {
      /*
       * Copy thread state so that the thread can be atomically NULLed.
       */
      memcpy (&threadCopy, tp, sizeof (threadCopy));

      /*
       * Thread ID structs are never freed. They're NULLed and reused.
       * This also sets the thread to PThreadStateInitial (invalid).
       */
      ptw32_threadReusePush (thread);

      /* Now work on the copy. */
      if (threadCopy.cancelEvent != NULL)
	{
	  CloseHandle (threadCopy.cancelEvent);
	}

#if ! (defined(__MINGW64__) || defined(__MINGW32__)) || defined (__MSVCRT__) || defined (__DMC__)
      /*
       * See documentation for endthread vs endthreadex.
       */
      if (threadCopy.threadH != 0)
	{
	  CloseHandle (threadCopy.threadH);
	}
#endif

    }
}
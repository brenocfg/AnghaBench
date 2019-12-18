#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* exitStatus; } ;
typedef  TYPE_1__ ptw32_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTW32_EPS_EXIT ; 
 int /*<<< orphan*/  _endthread () ; 
 int /*<<< orphan*/  _endthreadex (unsigned int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ pthread_count ; 
 scalar_t__ pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptw32_selfThreadKey ; 
 int /*<<< orphan*/  ptw32_throw (int /*<<< orphan*/ ) ; 

void
pthread_exit (void *value_ptr)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function terminates the calling thread, returning
      *      the value 'value_ptr' to any joining thread.
      *
      * PARAMETERS
      *      value_ptr
      *              a generic data value (i.e. not the address of a value)
      *
      *
      * DESCRIPTION
      *      This function terminates the calling thread, returning
      *      the value 'value_ptr' to any joining thread.
      *      NOTE: thread should be joinable.
      *
      * RESULTS
      *              N/A
      *
      * ------------------------------------------------------
      */
{
  ptw32_thread_t * sp;

  /*
   * Don't use pthread_self() to avoid creating an implicit POSIX thread handle
   * unnecessarily.
   */
  sp = (ptw32_thread_t *) pthread_getspecific (ptw32_selfThreadKey);

#if defined(_UWIN)
  if (--pthread_count <= 0)
    exit ((int) value_ptr);
#endif

  if (NULL == sp)
    {
      /*
       * A POSIX thread handle was never created. I.e. this is a
       * Win32 thread that has never called a pthreads-win32 routine that
       * required a POSIX handle.
       *
       * Implicit POSIX handles are cleaned up in ptw32_throw() now.
       */

#if ! (defined (__MINGW64__) || defined(__MINGW32__)) || defined (__MSVCRT__)  || defined (__DMC__)
      _endthreadex ((unsigned) (size_t) value_ptr);
#else
      _endthread ();
#endif

      /* Never reached */
    }

  sp->exitStatus = value_ptr;

  ptw32_throw (PTW32_EPS_EXIT);

  /* Never reached. */

}
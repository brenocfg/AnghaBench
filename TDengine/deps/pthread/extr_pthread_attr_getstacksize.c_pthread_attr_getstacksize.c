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
typedef  TYPE_1__* pthread_attr_t ;
struct TYPE_4__ {size_t stacksize; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 scalar_t__ ptw32_is_attr (TYPE_1__* const*) ; 

int
pthread_attr_getstacksize (const pthread_attr_t * attr, size_t * stacksize)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function determines the size of the stack on
      *      which threads created with 'attr' will run.
      *
      * PARAMETERS
      *      attr
      *              pointer to an instance of pthread_attr_t
      *
      *      stacksize
      *              pointer to size_t into which is returned the
      *              stack size, in bytes.
      *
      *
      * DESCRIPTION
      *      This function determines the size of the stack on
      *      which threads created with 'attr' will run.
      *
      *      NOTES:
      *              1)      Function supported only if this macro is
      *                      defined:
      *
      *                              _POSIX_THREAD_ATTR_STACKSIZE
      *
      *              2)      Use on newly created attributes object to
      *                      find the default stack size.
      *
      * RESULTS
      *              0               successfully retrieved stack size,
      *              EINVAL          'attr' is invalid
      *              ENOSYS          function not supported
      *
      * ------------------------------------------------------
      */
{
#if defined(_POSIX_THREAD_ATTR_STACKSIZE)

  if (ptw32_is_attr (attr) != 0)
    {
      return EINVAL;
    }

  /* Everything is okay. */
  *stacksize = (*attr)->stacksize;
  return 0;

#else

  return ENOSYS;

#endif /* _POSIX_THREAD_ATTR_STACKSIZE */

}
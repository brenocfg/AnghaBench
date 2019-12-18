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
struct TYPE_4__ {int detachstate; } ;

/* Variables and functions */
 int EINVAL ; 
 int PTHREAD_CREATE_DETACHED ; 
 scalar_t__ pte_is_attr (TYPE_1__* const*) ; 

int pthread_attr_getdetachstate (const pthread_attr_t * attr, int *detachstate)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function determines whether threads created with
    *      'attr' will run detached.
    *
    * PARAMETERS
    *      attr
    *              pointer to an instance of pthread_attr_t
    *
    *      detachstate
    *              pointer to an integer into which is returned one
    *              of:
    *
    *              PTHREAD_CREATE_JOINABLE
    *                              Thread ID is valid, must be joined
    *
    *              PTHREAD_CREATE_DETACHED
    *                              Thread ID is invalid, cannot be joined,
    *                              canceled, or modified
    *
    *
    * DESCRIPTION
    *      This function determines whether threads created with
    *      'attr' will run detached.
    *
    *      NOTES:
    *              1)      You cannot join or cancel detached threads.
    *
    * RESULTS
    *              0               successfully retrieved detach state,
    *              EINVAL          'attr' is invalid
    *
    * ------------------------------------------------------
    */
{
   if (pte_is_attr (attr) != 0 || detachstate == NULL)
   {
      *detachstate = PTHREAD_CREATE_DETACHED;
      return EINVAL;
   }

   *detachstate = (*attr)->detachstate;
   return 0;
}
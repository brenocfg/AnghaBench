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
typedef  TYPE_1__* pthread_rwlockattr_t ;
struct TYPE_3__ {int /*<<< orphan*/  pshared; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PTHREAD_PROCESS_PRIVATE ; 
 scalar_t__ calloc (int,int) ; 

int pthread_rwlockattr_init (pthread_rwlockattr_t * attr)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      Initializes a rwlock attributes object with default
    *      attributes.
    *
    * PARAMETERS
    *      attr
    *              pointer to an instance of pthread_rwlockattr_t
    *
    *
    * DESCRIPTION
    *      Initializes a rwlock attributes object with default
    *      attributes.
    *
    * RESULTS
    *              0               successfully initialized attr,
    *              ENOMEM          insufficient memory for attr.
    *
    * ------------------------------------------------------
    */
{
   int result = 0;
   pthread_rwlockattr_t rwa;

   rwa = (pthread_rwlockattr_t) calloc (1, sizeof (*rwa));

   if (rwa == NULL)
      result = ENOMEM;
   else
      rwa->pshared = PTHREAD_PROCESS_PRIVATE;

   *attr = rwa;

   return (result);
}
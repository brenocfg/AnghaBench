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
typedef  int /*<<< orphan*/ * pthread_rwlockattr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

int
pthread_rwlockattr_destroy (pthread_rwlockattr_t * attr)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      Destroys a rwlock attributes object. The object can
 *      no longer be used.
 *
 * PARAMETERS
 *      attr
 *              pointer to an instance of pthread_rwlockattr_t
 *
 *
 * DESCRIPTION
 *      Destroys a rwlock attributes object. The object can
 *      no longer be used.
 *
 *      NOTES:
 *              1)      Does not affect rwlockss created using 'attr'
 *
 * RESULTS
 *              0               successfully released attr,
 *              EINVAL          'attr' is invalid.
 *
 * ------------------------------------------------------
 */
{
   int result = 0;

   if (attr == NULL || *attr == NULL)
   {
      result = EINVAL;
   }
   else
   {
      pthread_rwlockattr_t rwa = *attr;

      *attr = NULL;
      free (rwa);
   }

   return (result);
}
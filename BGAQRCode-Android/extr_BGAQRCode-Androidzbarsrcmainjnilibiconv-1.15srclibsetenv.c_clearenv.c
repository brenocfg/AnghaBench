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

/* Variables and functions */
 int /*<<< orphan*/  LOCK ; 
 int /*<<< orphan*/  UNLOCK ; 
 int /*<<< orphan*/ * __environ ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * last_environ ; 

int
clearenv (void)
{
  LOCK;

  if (__environ == last_environ && __environ != NULL)
    {
      /* We allocated this environment so we can free it.  */
      free (__environ);
      last_environ = NULL;
    }

  /* Clear the environment pointer removes the whole environment.  */
  __environ = NULL;

  UNLOCK;

  return 0;
}
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
typedef  int /*<<< orphan*/  gomp_sem_t ;

/* Variables and functions */
 scalar_t__ sem_wait (int /*<<< orphan*/ *) ; 

void
gomp_sem_wait (gomp_sem_t *sem)
{
  /* With POSIX, the wait can be canceled by signals.  We don't want that.
     It is expected that the return value here is -1 and errno is EINTR.  */
  while (sem_wait (sem) != 0)
    continue;
}
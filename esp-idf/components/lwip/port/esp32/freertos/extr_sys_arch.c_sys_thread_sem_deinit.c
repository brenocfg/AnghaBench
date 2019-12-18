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
typedef  int /*<<< orphan*/  sys_sem_t ;

/* Variables and functions */
 int /*<<< orphan*/ * pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_thread_sem_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_thread_sem_key ; 

void
sys_thread_sem_deinit(void)
{
  sys_sem_t *sem = pthread_getspecific(sys_thread_sem_key);
  if (sem != NULL) {
    sys_thread_sem_free(sem);
    pthread_setspecific(sys_thread_sem_key, NULL);
  }
}
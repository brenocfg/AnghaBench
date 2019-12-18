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
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  fault_pages (int) ; 
 scalar_t__ num_threads ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ready_thread_count ; 
 int /*<<< orphan*/  ready_thread_count_lock ; 
 int /*<<< orphan*/  start_cvar ; 
 int /*<<< orphan*/  threads_ready_cvar ; 

__attribute__((used)) static void *thread_setup(void *arg)
{
  int my_index = *((int *)arg);

  T_QUIET; T_ASSERT_POSIX_SUCCESS(pthread_mutex_lock(&ready_thread_count_lock), "pthread_mutex_lock");
  ready_thread_count++;
  if(ready_thread_count == num_threads) {
    T_QUIET; T_ASSERT_POSIX_SUCCESS(pthread_cond_signal(&threads_ready_cvar), "pthread_cond_signal");
  }
  T_QUIET; T_ASSERT_POSIX_SUCCESS(pthread_cond_wait(&start_cvar, &ready_thread_count_lock), "pthread_cond_wait");
  T_QUIET; T_ASSERT_POSIX_SUCCESS(pthread_mutex_unlock(&ready_thread_count_lock), "pthread_mutex_unlock");

  fault_pages(my_index);
  return NULL;
}
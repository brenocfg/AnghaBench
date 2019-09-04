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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  SPIN_SECS ; 
 int /*<<< orphan*/  T_ASSERT_MACH_SUCCESS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pthread_setname_np (char*) ; 
 int /*<<< orphan*/  semaphore ; 
 int /*<<< orphan*/  semaphore_wait_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_for_duration (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  worker_sem ; 

__attribute__((used)) static void *
spin_thread(void *arg)
{
    uint32_t thread_id = (uint32_t) arg;
    char name[30] = "";

    snprintf(name, sizeof(name), "spin thread %2d", thread_id);
    pthread_setname_np(name);
    T_ASSERT_MACH_SUCCESS(semaphore_wait_signal(semaphore, worker_sem),
            "semaphore_wait_signal");
    spin_for_duration(SPIN_SECS);
    return NULL;
}
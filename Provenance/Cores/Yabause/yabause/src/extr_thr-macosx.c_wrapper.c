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
struct thd_s {int /*<<< orphan*/  mutex; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hnd_key ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *wrapper(void *hnd) {
    struct thd_s *hnds = (struct thd_s *)hnd;

    pthread_mutex_lock(&hnds->mutex);

    /* Set the handle for the thread, and call the actual thread function. */
    pthread_setspecific(hnd_key, hnd);
    hnds->func(hnds->arg);

    pthread_mutex_unlock(&hnds->mutex);

    return NULL;
}
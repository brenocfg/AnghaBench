#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ running; int /*<<< orphan*/ * func; int /*<<< orphan*/ * thd; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* thread_handle ; 

void YabThreadWait(unsigned int id) {
    /* Make sure the thread is running. */
    if(!thread_handle[id].running)
        return; 

    /* Join the thread to wait for it to finish. */
    pthread_join(thread_handle[id].thd, NULL);

    /* Cleanup... */
    pthread_cond_destroy(&thread_handle[id].cond);
    pthread_mutex_destroy(&thread_handle[id].mutex);
    thread_handle[id].thd = NULL;
    thread_handle[id].func = NULL;

    thread_handle[id].running = 0;
}
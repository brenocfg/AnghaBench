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
struct TYPE_3__ {int running; void (* func ) (void*) ;int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  thd; void* arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hnd_key_once ; 
 int /*<<< orphan*/  make_key ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__* thread_handle ; 
 int /*<<< orphan*/  wrapper ; 

int YabThreadStart(unsigned int id, void (*func)(void *), void *arg) {
    /* Create the key to access the thread handle if we haven't made it yet. */
    pthread_once(&hnd_key_once, make_key);

    /* Make sure we aren't trying to start a thread twice. */
    if(thread_handle[id].running) {
        fprintf(stderr, "YabThreadStart: Thread %u is already started!\n", id);
        return -1;
    }

    /* Create the mutex and condvar for the thread. */
    if(pthread_mutex_init(&thread_handle[id].mutex, NULL)) {
        fprintf(stderr, "YabThreadStart: Error creating mutex\n");
        return -1;
    }

    if(pthread_cond_init(&thread_handle[id].cond, NULL)) {
        fprintf(stderr, "YabThreadStart: Error creating condvar\n");
        pthread_mutex_destroy(&thread_handle[id].mutex);
        return -1;
    }

    thread_handle[id].func = func;
    thread_handle[id].arg = arg;

    /* Create the thread. */
    if(pthread_create(&thread_handle[id].thd, NULL, wrapper,
                      &thread_handle[id])) {
        fprintf(stderr, "YabThreadStart: Couldn't start thread\n");
        pthread_cond_destroy(&thread_handle[id].cond);
        pthread_mutex_destroy(&thread_handle[id].mutex);
        return -1;
    }

    thread_handle[id].running = 1;

    return 0;
}
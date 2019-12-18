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
typedef  int /*<<< orphan*/  pthread_mutex_t ;
typedef  int /*<<< orphan*/  pthread_cond_t ;
typedef  int /*<<< orphan*/  OMX_BUFFERHEADERTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void append_buffer(pthread_mutex_t *mutex, pthread_cond_t *cond,
                          int* array_size, OMX_BUFFERHEADERTYPE **array,
                          OMX_BUFFERHEADERTYPE *buffer)
{
    pthread_mutex_lock(mutex);
    array[(*array_size)++] = buffer;
    pthread_cond_broadcast(cond);
    pthread_mutex_unlock(mutex);
}
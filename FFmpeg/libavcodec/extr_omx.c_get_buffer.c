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
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static OMX_BUFFERHEADERTYPE *get_buffer(pthread_mutex_t *mutex, pthread_cond_t *cond,
                                        int* array_size, OMX_BUFFERHEADERTYPE **array,
                                        int wait)
{
    OMX_BUFFERHEADERTYPE *buffer;
    pthread_mutex_lock(mutex);
    if (wait) {
        while (!*array_size)
           pthread_cond_wait(cond, mutex);
    }
    if (*array_size > 0) {
        buffer = array[0];
        (*array_size)--;
        memmove(&array[0], &array[1], (*array_size) * sizeof(OMX_BUFFERHEADERTYPE*));
    } else {
        buffer = NULL;
    }
    pthread_mutex_unlock(mutex);
    return buffer;
}
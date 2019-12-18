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
 int /*<<< orphan*/  PTHREAD_TLS_INDEX ; 
 int /*<<< orphan*/  pthread_local_storage_thread_deleted_callback (int /*<<< orphan*/ ,void*) ; 
 void* pvTaskGetThreadLocalStoragePointer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskSetThreadLocalStoragePointer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskSetThreadLocalStoragePointerAndDelCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void pthread_internal_local_storage_destructor_callback(void)
{
    void *tls = pvTaskGetThreadLocalStoragePointer(NULL, PTHREAD_TLS_INDEX);
    if (tls != NULL) {
        pthread_local_storage_thread_deleted_callback(PTHREAD_TLS_INDEX, tls);
        /* remove the thread-local-storage pointer to avoid the idle task cleanup
           calling it again...
        */
#if defined(CONFIG_FREERTOS_ENABLE_STATIC_TASK_CLEAN_UP)
        vTaskSetThreadLocalStoragePointer(NULL, PTHREAD_TLS_INDEX, NULL);
#else
        vTaskSetThreadLocalStoragePointerAndDelCallback(NULL,
                                                        PTHREAD_TLS_INDEX,
                                                        NULL,
                                                        NULL);
#endif
    }
}
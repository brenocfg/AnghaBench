#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  state; scalar_t__ join_task; void* retval; scalar_t__ detached; scalar_t__ task_arg; } ;
typedef  TYPE_1__ esp_pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTHREAD_TASK_STATE_EXIT ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eNoAction ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  pthread_delete (TYPE_1__*) ; 
 TYPE_1__* pthread_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_internal_local_storage_destructor_callback () ; 
 int /*<<< orphan*/  s_threads_mux ; 
 int /*<<< orphan*/  uxTaskGetStackHighWaterMark (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskSuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 scalar_t__ xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTaskGetCurrentTaskHandle () ; 
 int /*<<< orphan*/  xTaskNotify (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pthread_exit(void *value_ptr)
{
    bool detached = false;
    /* preemptively clean up thread local storage, rather than
       waiting for the idle task to clean up the thread */
    pthread_internal_local_storage_destructor_callback();

    if (xSemaphoreTake(s_threads_mux, portMAX_DELAY) != pdTRUE) {
        assert(false && "Failed to lock threads list!");
    }
    esp_pthread_t *pthread = pthread_find(xTaskGetCurrentTaskHandle());
    if (!pthread) {
        assert(false && "Failed to find pthread for current task!");
    }
    if (pthread->task_arg) {
        free(pthread->task_arg);
    }
    if (pthread->detached) {
        // auto-free for detached threads
        pthread_delete(pthread);
        detached = true;
    } else {
        // Set return value
        pthread->retval = value_ptr;
        // Remove from list, it indicates that task has exited
        if (pthread->join_task) {
            // notify join
            xTaskNotify(pthread->join_task, 0, eNoAction);
        } else {
            pthread->state = PTHREAD_TASK_STATE_EXIT;
        }
    }
    xSemaphoreGive(s_threads_mux);

    ESP_LOGD(TAG, "Task stk_wm = %d", uxTaskGetStackHighWaterMark(NULL));

    if (detached) {
        vTaskDelete(NULL);
    } else {
        vTaskSuspend(NULL);
    }

    // Should never be reached
    abort();
}
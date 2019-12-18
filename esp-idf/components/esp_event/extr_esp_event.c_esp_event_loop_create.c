#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_event_post_instance_t ;
struct TYPE_9__ {char* name; int /*<<< orphan*/ * profiling_mutex; int /*<<< orphan*/ * mutex; int /*<<< orphan*/ * queue; int /*<<< orphan*/ * running_task; int /*<<< orphan*/ * task; int /*<<< orphan*/  loop_nodes; } ;
typedef  TYPE_1__ esp_event_loop_instance_t ;
typedef  scalar_t__ esp_event_loop_handle_t ;
struct TYPE_10__ {char* task_name; int /*<<< orphan*/  task_core_id; int /*<<< orphan*/  task_priority; int /*<<< orphan*/  task_stack_size; int /*<<< orphan*/  queue_size; } ;
typedef  TYPE_2__ esp_event_loop_args_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (TYPE_2__ const*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  esp_event_loop_run_task ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  next ; 
 scalar_t__ pdPASS ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_event_loops ; 
 int /*<<< orphan*/  s_event_loops_spinlock ; 
 int /*<<< orphan*/  vQueueDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xQueueCreate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xSemaphoreCreateMutex () ; 
 int /*<<< orphan*/ * xSemaphoreCreateRecursiveMutex () ; 
 scalar_t__ xTaskCreatePinnedToCore (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

esp_err_t esp_event_loop_create(const esp_event_loop_args_t* event_loop_args, esp_event_loop_handle_t* event_loop)
{
    assert(event_loop_args);

    esp_event_loop_instance_t* loop;
    esp_err_t err = ESP_ERR_NO_MEM; // most likely error

    loop = calloc(1, sizeof(*loop));
    if (loop == NULL) {
        ESP_LOGE(TAG, "alloc for event loop failed");
        return err;
    }

    loop->queue = xQueueCreate(event_loop_args->queue_size , sizeof(esp_event_post_instance_t));
    if (loop->queue == NULL) {
        ESP_LOGE(TAG, "create event loop queue failed");
        goto on_err;
    }

    loop->mutex = xSemaphoreCreateRecursiveMutex();
    if (loop->mutex == NULL) {
        ESP_LOGE(TAG, "create event loop mutex failed");
        goto on_err;
    }

#ifdef CONFIG_ESP_EVENT_LOOP_PROFILING
    loop->profiling_mutex = xSemaphoreCreateMutex();
    if (loop->profiling_mutex == NULL) {
        ESP_LOGE(TAG, "create event loop profiling mutex failed");
        goto on_err;
    }
#endif

    SLIST_INIT(&(loop->loop_nodes));

    // Create the loop task if requested
    if (event_loop_args->task_name != NULL) {
        BaseType_t task_created = xTaskCreatePinnedToCore(esp_event_loop_run_task, event_loop_args->task_name,
                    event_loop_args->task_stack_size, (void*) loop,
                    event_loop_args->task_priority, &(loop->task), event_loop_args->task_core_id);

        if (task_created != pdPASS) {
            ESP_LOGE(TAG, "create task for loop failed");
            err = ESP_FAIL;
            goto on_err;
        }

        loop->name = event_loop_args->task_name;

        ESP_LOGD(TAG, "created task for loop %p", loop);
    } else {
        loop->name = "";
        loop->task = NULL;
    }

    loop->running_task = NULL;

#ifdef CONFIG_ESP_EVENT_LOOP_PROFILING
    portENTER_CRITICAL(&s_event_loops_spinlock);
    SLIST_INSERT_HEAD(&s_event_loops, loop, next);
    portEXIT_CRITICAL(&s_event_loops_spinlock);
#endif

    *event_loop = (esp_event_loop_handle_t) loop;

    ESP_LOGD(TAG, "created event loop %p", loop);

    return ESP_OK;

on_err:
    if (loop->queue != NULL) {
        vQueueDelete(loop->queue);
    }

    if (loop->mutex != NULL) {
        vSemaphoreDelete(loop->mutex);
    }

#ifdef CONFIG_ESP_EVENT_LOOP_PROFILING
    if (loop->profiling_mutex != NULL) {
        vSemaphoreDelete(loop->profiling_mutex);
    }
#endif

    free(loop);

    return err;
}
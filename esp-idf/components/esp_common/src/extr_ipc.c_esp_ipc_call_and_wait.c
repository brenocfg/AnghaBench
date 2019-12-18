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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  esp_ipc_wait_t ;
typedef  int /*<<< orphan*/  esp_ipc_func_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  scalar_t__ UBaseType_t ;
typedef  int /*<<< orphan*/  TaskHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 size_t portNUM_PROCESSORS ; 
 int /*<<< orphan*/ * s_func ; 
 void** s_func_arg ; 
 int /*<<< orphan*/ * s_ipc_ack ; 
 int /*<<< orphan*/ * s_ipc_mutex ; 
 int /*<<< orphan*/ * s_ipc_sem ; 
 int /*<<< orphan*/ * s_ipc_task_handle ; 
 int /*<<< orphan*/ * s_ipc_wait ; 
 scalar_t__ taskSCHEDULER_RUNNING ; 
 scalar_t__ uxTaskPriorityGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskPrioritySet (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTaskGetCurrentTaskHandle () ; 
 scalar_t__ xTaskGetSchedulerState () ; 

__attribute__((used)) static esp_err_t esp_ipc_call_and_wait(uint32_t cpu_id, esp_ipc_func_t func, void* arg, esp_ipc_wait_t wait_for)
{
    if (cpu_id >= portNUM_PROCESSORS) {
        return ESP_ERR_INVALID_ARG;
    }
    if (xTaskGetSchedulerState() != taskSCHEDULER_RUNNING) {
        return ESP_ERR_INVALID_STATE;
    }

#ifdef CONFIG_ESP_IPC_USES_CALLERS_PRIORITY
    TaskHandle_t task_handler = xTaskGetCurrentTaskHandle();
    UBaseType_t priority_of_current_task = uxTaskPriorityGet(task_handler);
    UBaseType_t priority_of_running_ipc_task = uxTaskPriorityGet(s_ipc_task_handle[cpu_id]);
    if (priority_of_running_ipc_task < priority_of_current_task) {
        vTaskPrioritySet(s_ipc_task_handle[cpu_id], priority_of_current_task);
    }

    xSemaphoreTake(s_ipc_mutex[cpu_id], portMAX_DELAY);
    vTaskPrioritySet(s_ipc_task_handle[cpu_id], priority_of_current_task);
#else
    xSemaphoreTake(s_ipc_mutex[0], portMAX_DELAY);
#endif

    s_func[cpu_id] = func;
    s_func_arg[cpu_id] = arg;
    s_ipc_wait[cpu_id] = wait_for;
    xSemaphoreGive(s_ipc_sem[cpu_id]);
    xSemaphoreTake(s_ipc_ack[cpu_id], portMAX_DELAY);
#ifdef CONFIG_ESP_IPC_USES_CALLERS_PRIORITY
    xSemaphoreGive(s_ipc_mutex[cpu_id]);
#else
    xSemaphoreGive(s_ipc_mutex[0]);
#endif
    return ESP_OK;
}
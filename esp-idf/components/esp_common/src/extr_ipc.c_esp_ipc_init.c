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
typedef  int /*<<< orphan*/  task_name ;
typedef  scalar_t__ portBASE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ESP_IPC_TASK_STACK_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ configMAX_PRIORITIES ; 
 int /*<<< orphan*/  ipc_task ; 
 scalar_t__ pdTRUE ; 
 int portNUM_PROCESSORS ; 
 void** s_ipc_ack ; 
 int /*<<< orphan*/ * s_ipc_mutex ; 
 void** s_ipc_sem ; 
 int /*<<< orphan*/ * s_ipc_task_handle ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 void* xSemaphoreCreateBinary () ; 
 int /*<<< orphan*/  xSemaphoreCreateMutex () ; 
 scalar_t__ xTaskCreatePinnedToCore (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void esp_ipc_init(void)
{
    char task_name[15];
    for (int i = 0; i < portNUM_PROCESSORS; ++i) {
        snprintf(task_name, sizeof(task_name), "ipc%d", i);
        s_ipc_mutex[i] = xSemaphoreCreateMutex();
        s_ipc_ack[i] = xSemaphoreCreateBinary();
        s_ipc_sem[i] = xSemaphoreCreateBinary();
        portBASE_TYPE res = xTaskCreatePinnedToCore(ipc_task, task_name, CONFIG_ESP_IPC_TASK_STACK_SIZE, (void*) i,
                                                    configMAX_PRIORITIES - 1, &s_ipc_task_handle[i], i);
        assert(res == pdTRUE);
    }
}
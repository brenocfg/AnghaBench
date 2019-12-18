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
typedef  int /*<<< orphan*/ * sys_thread_t ;
typedef  int /*<<< orphan*/  lwip_thread_fn ;
typedef  int /*<<< orphan*/  TaskHandle_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_LWIP_TCPIP_TASK_AFFINITY ; 
 scalar_t__ pdTRUE ; 
 scalar_t__ xTaskCreatePinnedToCore (int /*<<< orphan*/ ,char const*,int,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

sys_thread_t
sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
{
  TaskHandle_t rtos_task;
  BaseType_t ret;

  /* LwIP's lwip_thread_fn matches FreeRTOS' TaskFunction_t, so we can pass the
     thread function without adaption here. */
  ret = xTaskCreatePinnedToCore(thread, name, stacksize, arg, prio, &rtos_task,
          CONFIG_LWIP_TCPIP_TASK_AFFINITY);

  if (ret != pdTRUE) {
    return NULL;
  }

  return (sys_thread_t)rtos_task;
}
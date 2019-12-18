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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  QueueHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCOUNT ; 
 int /*<<< orphan*/  RSR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int flag ; 
 int /*<<< orphan*/  trigger ; 
 int /*<<< orphan*/  xQueueSendToBack (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void task_send_to_queue(void *param)
{
    QueueHandle_t queue = (QueueHandle_t) param;
    uint32_t ccount;

    while(!trigger) {}

    RSR(CCOUNT, ccount);
    flag = true;
    xQueueSendToBack(queue, &ccount, 0);
    /* This is to ensure that higher priority task
       won't wake anyhow, due to this task terminating.

       The task runs until terminated by the main task.
    */
    while(1) {}
}
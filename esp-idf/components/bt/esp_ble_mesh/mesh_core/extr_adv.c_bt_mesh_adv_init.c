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
typedef  int /*<<< orphan*/  bt_mesh_msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADV_TASK_CORE ; 
 int /*<<< orphan*/  BLE_MESH_QUEUE_SET_SIZE ; 
 int /*<<< orphan*/  BLE_MESH_QUEUE_SIZE ; 
 int /*<<< orphan*/  BLE_MESH_RELAY_QUEUE_SIZE ; 
 int /*<<< orphan*/  adv_thread ; 
 int /*<<< orphan*/  configASSERT (int) ; 
 scalar_t__ configMAX_PRIORITIES ; 
 int pdTRUE ; 
 int xBleMeshQueue ; 
 int xBleMeshQueueSet ; 
 int xBleMeshRelayQueue ; 
 int /*<<< orphan*/  xQueueAddToSet (int,int) ; 
 int xQueueCreate (int /*<<< orphan*/ ,int) ; 
 int xQueueCreateSet (int /*<<< orphan*/ ) ; 
 int xTaskCreatePinnedToCore (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bt_mesh_adv_init(void)
{
    xBleMeshQueue = xQueueCreate(BLE_MESH_QUEUE_SIZE, sizeof(bt_mesh_msg_t));
    configASSERT(xBleMeshQueue);
#if defined(CONFIG_BLE_MESH_RELAY_ADV_BUF)
    xBleMeshRelayQueue = xQueueCreate(BLE_MESH_RELAY_QUEUE_SIZE, sizeof(bt_mesh_msg_t));
    configASSERT(xBleMeshRelayQueue);
    xBleMeshQueueSet = xQueueCreateSet(BLE_MESH_QUEUE_SET_SIZE);
    configASSERT(xBleMeshQueueSet);
    xQueueAddToSet(xBleMeshQueue, xBleMeshQueueSet);
    xQueueAddToSet(xBleMeshRelayQueue, xBleMeshQueueSet);
#endif /* defined(CONFIG_BLE_MESH_RELAY_ADV_BUF) */
    int ret = xTaskCreatePinnedToCore(adv_thread, "BLE_Mesh_ADV_Task", 3072, NULL,
                                      configMAX_PRIORITIES - 7, NULL, ADV_TASK_CORE);
    configASSERT(ret == pdTRUE);
}
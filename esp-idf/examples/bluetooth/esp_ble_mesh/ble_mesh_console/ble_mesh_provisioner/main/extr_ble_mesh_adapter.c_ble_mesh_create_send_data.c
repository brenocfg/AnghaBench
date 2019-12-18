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
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
#define  ESP_BLE_MESH_VND_MODEL_OP_TEST_PERF_GET 130 
#define  ESP_BLE_MESH_VND_MODEL_OP_TEST_PERF_SET 129 
#define  ESP_BLE_MESH_VND_MODEL_OP_TEST_PERF_SET_UNACK 128 
 char VENDOR_MODEL_PERF_OPERATION_TYPE_GET ; 
 char VENDOR_MODEL_PERF_OPERATION_TYPE_SET ; 
 char VENDOR_MODEL_PERF_OPERATION_TYPE_SET_UNACK ; 

void ble_mesh_create_send_data(char *data, uint16_t byte_num, uint16_t sequence_num, uint32_t opcode)
{
    uint16_t i;

    // first two bytes are sequence num, third is type
    data[0] = sequence_num >> 8;
    data[1] = sequence_num & 0xFF;
    switch (opcode) {
    case ESP_BLE_MESH_VND_MODEL_OP_TEST_PERF_GET:
        data[2] = VENDOR_MODEL_PERF_OPERATION_TYPE_GET;
        break;
    case ESP_BLE_MESH_VND_MODEL_OP_TEST_PERF_SET:
        data[2] = VENDOR_MODEL_PERF_OPERATION_TYPE_SET;
        break;
    case ESP_BLE_MESH_VND_MODEL_OP_TEST_PERF_SET_UNACK:
        data[2] = VENDOR_MODEL_PERF_OPERATION_TYPE_SET_UNACK;
        break;
    }

    for (i = 3; i < byte_num; i++) {
        data[i] = i;
    }
}
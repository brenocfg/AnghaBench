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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sys_cpu_to_be16 (int) ; 
 int /*<<< orphan*/  sys_cpu_to_le16 (int) ; 

esp_err_t esp_ble_mesh_model_msg_opcode_init(uint8_t *data, uint32_t opcode)
{
    uint16_t val;

    if (data == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (opcode < 0x100) {
        /* 1-byte OpCode */
        data[0] = opcode & 0xff;
        return ESP_OK;
    }

    if (opcode < 0x10000) {
        /* 2-byte OpCode, big endian */
        val = sys_cpu_to_be16 (opcode);
        memcpy(data, &val, 2);
        return ESP_OK;
    }

    /* 3-byte OpCode, note that little endian for the least 2 bytes(Company ID) of opcode */
    data[0] = (opcode >> 16) & 0xff;
    val = sys_cpu_to_le16(opcode & 0xffff);
    memcpy(&data[1], &val, 2);

    return ESP_OK;
}
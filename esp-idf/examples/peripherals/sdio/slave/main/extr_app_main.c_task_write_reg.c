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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOG_BUFFER_HEXDUMP (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOG_INFO ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ sdio_slave_read_reg (int) ; 
 int /*<<< orphan*/  sdio_slave_write_reg (int,scalar_t__) ; 

__attribute__((used)) static esp_err_t task_write_reg(void)
{
    //the host write REG1, the slave should write its registers according to value of REG1
    uint8_t read = sdio_slave_read_reg(1);
    for (int i = 0; i < 64; i++) {
        //skip interrupt regs.
        if (i >= 28 && i <= 31) continue;
        sdio_slave_write_reg(i, read+3*i);
    }
    uint8_t reg[64] = {0};
    for (int i = 0; i < 64; i++) {
        //skip interrupt regs.
        if (i >= 28 && i <= 31) continue;
        reg[i] = sdio_slave_read_reg(i);
    }
    ESP_LOGI(TAG, "write regs:");
    ESP_LOG_BUFFER_HEXDUMP(TAG, reg, 64, ESP_LOG_INFO);
    return ESP_OK;
}
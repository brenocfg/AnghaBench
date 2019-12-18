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
typedef  int /*<<< orphan*/  esp_slave_context_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  HOST_SLCHOST_CONF_W_REG (int) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_slave_write_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 

esp_err_t esp_slave_write_reg(esp_slave_context_t *context, uint8_t addr, uint8_t value, uint8_t* value_o)
{
    ESP_LOGV(TAG, "write_reg: %08X", value);
    // addrress over range
    if (addr >= 64) return ESP_ERR_INVALID_ARG;
    // reserved for interrupts
    if (addr >= 28 && addr <= 31) return ESP_ERR_INVALID_ARG;
    return esp_slave_write_byte(context, HOST_SLCHOST_CONF_W_REG(addr), value, value_o);
}
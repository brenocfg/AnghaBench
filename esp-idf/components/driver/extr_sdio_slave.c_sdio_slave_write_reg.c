#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_2__ {int /*<<< orphan*/  reg_spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int HOST_SLCHOST_CONF_W_REG (int) ; 
 int /*<<< orphan*/  SDIO_SLAVE_LOGE (char*) ; 
 TYPE_1__ context ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 

esp_err_t sdio_slave_write_reg(int pos, uint8_t reg)
{
    if (pos >= 28 && pos <= 31) {
        SDIO_SLAVE_LOGE("interrupt reg, please use sdio_slave_clear_int");
        return ESP_ERR_INVALID_ARG;
    }
    if (pos < 0 || pos >= 64) {
        SDIO_SLAVE_LOGE("write register address wrong");
        return ESP_ERR_INVALID_ARG;
    }
    uint32_t addr = HOST_SLCHOST_CONF_W_REG(pos) & (~3);
    uint32_t shift = (pos % 4)*8;

    portENTER_CRITICAL(&context.reg_spinlock);
    int val = *(uint32_t*)addr;
    *(uint32_t*)addr = (val & ~(0xff << shift)) | (reg<<shift);
    portEXIT_CRITICAL(&context.reg_spinlock);
    return ESP_OK;
}
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
typedef  scalar_t__ i2c_port_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ I2C_NUM_0 ; 
 scalar_t__ I2C_NUM_1 ; 
 int /*<<< orphan*/  PERIPH_I2C0_MODULE ; 
 int /*<<< orphan*/  PERIPH_I2C1_MODULE ; 
 int /*<<< orphan*/  periph_module_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t i2c_hw_disable(i2c_port_t i2c_num)
{
    if (i2c_num == I2C_NUM_0) {
        periph_module_disable(PERIPH_I2C0_MODULE);
    } else if (i2c_num == I2C_NUM_1) {
        periph_module_disable(PERIPH_I2C1_MODULE);
    }
    return ESP_OK;
}
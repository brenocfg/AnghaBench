#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  clk_speed; } ;
struct TYPE_5__ {TYPE_1__ master; int /*<<< orphan*/  scl_pullup_en; int /*<<< orphan*/  scl_io_num; int /*<<< orphan*/  sda_pullup_en; int /*<<< orphan*/  sda_io_num; int /*<<< orphan*/  mode; } ;
typedef  TYPE_2__ i2c_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_PULLUP_ENABLE ; 
 int /*<<< orphan*/  I2C_MODE_MASTER ; 
 int /*<<< orphan*/  i2c_frequency ; 
 int /*<<< orphan*/  i2c_gpio_scl ; 
 int /*<<< orphan*/  i2c_gpio_sda ; 
 int /*<<< orphan*/  i2c_param_config (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_port ; 

__attribute__((used)) static esp_err_t i2c_master_driver_initialize(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = i2c_gpio_sda,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = i2c_gpio_scl,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = i2c_frequency
    };
    return i2c_param_config(i2c_port, &conf);
}
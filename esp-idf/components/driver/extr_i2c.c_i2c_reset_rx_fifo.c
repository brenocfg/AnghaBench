#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t i2c_port_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int rx_fifo_rst; } ;
struct TYPE_4__ {TYPE_1__ fifo_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__** I2C ; 
 int /*<<< orphan*/  I2C_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_ENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  I2C_EXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  I2C_NUM_ERROR_STR ; 
 size_t I2C_NUM_MAX ; 
 int /*<<< orphan*/ * i2c_spinlock ; 

esp_err_t i2c_reset_rx_fifo(i2c_port_t i2c_num)
{
    I2C_CHECK(i2c_num < I2C_NUM_MAX, I2C_NUM_ERROR_STR, ESP_ERR_INVALID_ARG);
    I2C_ENTER_CRITICAL(&i2c_spinlock[i2c_num]);
    I2C[i2c_num]->fifo_conf.rx_fifo_rst = 1;
    I2C[i2c_num]->fifo_conf.rx_fifo_rst = 0;
    I2C_EXIT_CRITICAL(&i2c_spinlock[i2c_num]);
    return ESP_OK;
}
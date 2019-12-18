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
typedef  int /*<<< orphan*/  xSemaphoreHandle ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  i2c_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_LENGTH ; 
 int /*<<< orphan*/  I2C_MODE_SLAVE ; 
 int /*<<< orphan*/  I2C_SLAVE_NUM ; 
 int /*<<< orphan*/  I2C_SLAVE_RX_BUF_LEN ; 
 int /*<<< orphan*/  I2C_SLAVE_TX_BUF_LEN ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int exit_flag ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_driver_install (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_param_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_slave_init () ; 
 int /*<<< orphan*/  i2c_slave_read_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_slave_write_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ test_read_func ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_task(void *pvParameters)
{
    xSemaphoreHandle *sema = (xSemaphoreHandle *) pvParameters;

    uint8_t *data = (uint8_t *) malloc(DATA_LENGTH);
    i2c_config_t conf_slave = i2c_slave_init();
    TEST_ESP_OK(i2c_param_config( I2C_SLAVE_NUM, &conf_slave));
    TEST_ESP_OK(i2c_driver_install(I2C_SLAVE_NUM, I2C_MODE_SLAVE,
                                   I2C_SLAVE_RX_BUF_LEN,
                                   I2C_SLAVE_TX_BUF_LEN, 0));
    while (exit_flag == false) {
        if (test_read_func) {
            i2c_slave_read_buffer(I2C_SLAVE_NUM, data, DATA_LENGTH, 0);
        } else {
            i2c_slave_write_buffer(I2C_SLAVE_NUM, data, DATA_LENGTH, 0);
        }
    }

    free(data);
    xSemaphoreGive(*sema);
    vTaskDelete(NULL);
}
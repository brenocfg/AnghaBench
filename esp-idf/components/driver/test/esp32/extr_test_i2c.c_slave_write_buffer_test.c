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
typedef  int /*<<< orphan*/  i2c_config_t ;

/* Variables and functions */
 int DATA_LENGTH ; 
 int /*<<< orphan*/  I2C_MODE_SLAVE ; 
 int /*<<< orphan*/  I2C_SLAVE_NUM ; 
 int /*<<< orphan*/  I2C_SLAVE_RX_BUF_LEN ; 
 int /*<<< orphan*/  I2C_SLAVE_TX_BUF_LEN ; 
 int /*<<< orphan*/  RW_TEST_LENGTH ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disp_buf (int*,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  i2c_driver_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_driver_install (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_param_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_slave_init () ; 
 int i2c_slave_write_buffer (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ malloc (int) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  unity_send_signal (char*) ; 
 int /*<<< orphan*/  unity_wait_for_signal (char*) ; 

__attribute__((used)) static void slave_write_buffer_test(void)
{
    uint8_t *data_wr = (uint8_t *) malloc(DATA_LENGTH);
    int size_rd;

    i2c_config_t conf_slave = i2c_slave_init();
    TEST_ESP_OK(i2c_param_config( I2C_SLAVE_NUM, &conf_slave));
    TEST_ESP_OK(i2c_driver_install(I2C_SLAVE_NUM, I2C_MODE_SLAVE,
                                   I2C_SLAVE_RX_BUF_LEN,
                                   I2C_SLAVE_TX_BUF_LEN, 0));
    unity_send_signal("i2c slave init finish");

    unity_wait_for_signal("slave write");
    for (int i = 0; i < DATA_LENGTH / 2; i++) {
        data_wr[i] = i;
    }
    size_rd = i2c_slave_write_buffer(I2C_SLAVE_NUM, data_wr, RW_TEST_LENGTH, 2000 / portTICK_RATE_MS);
    disp_buf(data_wr, size_rd);
    unity_send_signal("master read");
    unity_wait_for_signal("ready to delete");
    free(data_wr);
    i2c_driver_delete(I2C_SLAVE_NUM);
}
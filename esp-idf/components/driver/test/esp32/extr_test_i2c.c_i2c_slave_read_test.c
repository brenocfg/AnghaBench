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
 int /*<<< orphan*/  DATA_LENGTH ; 
 int /*<<< orphan*/  I2C_MODE_SLAVE ; 
 int /*<<< orphan*/  I2C_SLAVE_NUM ; 
 int /*<<< orphan*/  I2C_SLAVE_RX_BUF_LEN ; 
 int /*<<< orphan*/  I2C_SLAVE_TX_BUF_LEN ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disp_buf (int*,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  i2c_driver_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_driver_install (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_param_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_slave_init () ; 
 int i2c_slave_read_buffer (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  unity_send_signal (char*) ; 
 int /*<<< orphan*/  unity_wait_for_signal (char*) ; 

__attribute__((used)) static void i2c_slave_read_test(void)
{
    uint8_t *data_rd = (uint8_t *) malloc(DATA_LENGTH);
    int size_rd = 0;
    int len = 0;

    i2c_config_t conf_slave = i2c_slave_init();
    TEST_ESP_OK(i2c_param_config( I2C_SLAVE_NUM, &conf_slave));
    TEST_ESP_OK(i2c_driver_install(I2C_SLAVE_NUM, I2C_MODE_SLAVE,
                                   I2C_SLAVE_RX_BUF_LEN,
                                   I2C_SLAVE_TX_BUF_LEN, 0));
    unity_send_signal("i2c slave init finish");

    unity_wait_for_signal("master write");
    while (1) {
        len = i2c_slave_read_buffer( I2C_SLAVE_NUM, data_rd + size_rd, DATA_LENGTH, 10000 / portTICK_RATE_MS);
        if (len == 0) {
            break;
        }
        size_rd += len;
    }
    disp_buf(data_rd, size_rd);
    for (int i = 0; i < size_rd; i++) {
        TEST_ASSERT(data_rd[i] == i);
    }
    free(data_rd);
    unity_send_signal("ready to delete");
    TEST_ESP_OK(i2c_driver_delete(I2C_SLAVE_NUM));
}
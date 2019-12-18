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
typedef  int /*<<< orphan*/  i2c_cmd_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_CHECK_EN ; 
 int /*<<< orphan*/  ACK_VAL ; 
 int /*<<< orphan*/  DATA_LENGTH ; 
 int ESP_SLAVE_ADDR ; 
 int /*<<< orphan*/  I2C_MASTER_NUM ; 
 int /*<<< orphan*/  I2C_MASTER_RX_BUF_DISABLE ; 
 int /*<<< orphan*/  I2C_MASTER_TX_BUF_DISABLE ; 
 int /*<<< orphan*/  I2C_MODE_MASTER ; 
 int /*<<< orphan*/  NACK_VAL ; 
 int READ_BIT ; 
 int RW_TEST_LENGTH ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  i2c_cmd_link_create () ; 
 int /*<<< orphan*/  i2c_cmd_link_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_driver_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_driver_install (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_cmd_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_master_init () ; 
 int /*<<< orphan*/  i2c_master_read (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_read_byte (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_write_byte (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_param_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  unity_send_signal (char*) ; 
 int /*<<< orphan*/  unity_wait_for_signal (char*) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void master_read_slave_test(void)
{
    uint8_t *data_rd = (uint8_t *) malloc(DATA_LENGTH);
    memset(data_rd, 0, DATA_LENGTH);
    i2c_config_t conf_master = i2c_master_init();
    TEST_ESP_OK(i2c_param_config(I2C_MASTER_NUM, &conf_master));
    TEST_ESP_OK(i2c_driver_install(I2C_MASTER_NUM, I2C_MODE_MASTER,
                                   I2C_MASTER_RX_BUF_DISABLE,
                                   I2C_MASTER_TX_BUF_DISABLE, 0));
    unity_wait_for_signal("i2c slave init finish");

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, ( ESP_SLAVE_ADDR << 1 ) | READ_BIT, ACK_CHECK_EN);

    unity_send_signal("slave write");
    unity_wait_for_signal("master read");
    i2c_master_read(cmd, data_rd, RW_TEST_LENGTH-1, ACK_VAL);
    i2c_master_read_byte(cmd, data_rd + RW_TEST_LENGTH-1, NACK_VAL);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 5000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    vTaskDelay(100 / portTICK_RATE_MS);
    for (int i = 0; i < RW_TEST_LENGTH; i++) {
        printf("%d\n", data_rd[i]);
        TEST_ASSERT(data_rd[i]==i);
    }
    free(data_rd);
    unity_send_signal("ready to delete");
    i2c_driver_delete(I2C_MASTER_NUM);
}
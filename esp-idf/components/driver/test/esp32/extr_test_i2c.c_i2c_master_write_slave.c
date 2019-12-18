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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  i2c_port_t ;
typedef  int /*<<< orphan*/  i2c_cmd_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_CHECK_EN ; 
 int ESP_SLAVE_ADDR ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int WRITE_BIT ; 
 int /*<<< orphan*/  i2c_cmd_link_create () ; 
 int /*<<< orphan*/  i2c_cmd_link_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_cmd_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_master_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_write_byte (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int portTICK_RATE_MS ; 

__attribute__((used)) static esp_err_t i2c_master_write_slave(i2c_port_t i2c_num, uint8_t *data_wr, size_t size)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    TEST_ESP_OK(i2c_master_write_byte(cmd, ( ESP_SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN));
    TEST_ESP_OK(i2c_master_write(cmd, data_wr, size, ACK_CHECK_EN));
    TEST_ESP_OK(i2c_master_stop(cmd));
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 5000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}
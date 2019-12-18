#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i2c_cmd_handle_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_8__ {TYPE_3__* data; TYPE_2__* register_address; TYPE_1__* chip_address; int /*<<< orphan*/  end; } ;
struct TYPE_7__ {int count; int* ival; } ;
struct TYPE_6__ {int* ival; scalar_t__ count; } ;
struct TYPE_5__ {int* ival; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_CHECK_EN ; 
 scalar_t__ ESP_ERR_TIMEOUT ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  I2C_MASTER_RX_BUF_DISABLE ; 
 int /*<<< orphan*/  I2C_MASTER_TX_BUF_DISABLE ; 
 int /*<<< orphan*/  I2C_MODE_MASTER ; 
 int /*<<< orphan*/  TAG ; 
 int WRITE_BIT ; 
 int arg_parse (int,char**,void**) ; 
 int /*<<< orphan*/  arg_print_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i2c_cmd_link_create () ; 
 int /*<<< orphan*/  i2c_cmd_link_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_driver_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_driver_install (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_master_cmd_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_master_driver_initialize () ; 
 int /*<<< orphan*/  i2c_master_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_write_byte (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_port ; 
 TYPE_4__ i2cset_args ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int do_i2cset_cmd(int argc, char **argv)
{
    int nerrors = arg_parse(argc, argv, (void **)&i2cset_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, i2cset_args.end, argv[0]);
        return 0;
    }

    /* Check chip address: "-c" option */
    int chip_addr = i2cset_args.chip_address->ival[0];
    /* Check register address: "-r" option */
    int data_addr = 0;
    if (i2cset_args.register_address->count) {
        data_addr = i2cset_args.register_address->ival[0];
    }
    /* Check data: "-d" option */
    int len = i2cset_args.data->count;

    i2c_master_driver_initialize();
    i2c_driver_install(i2c_port, I2C_MODE_MASTER, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, chip_addr << 1 | WRITE_BIT, ACK_CHECK_EN);
    if (i2cset_args.register_address->count) {
        i2c_master_write_byte(cmd, data_addr, ACK_CHECK_EN);
    }
    for (int i = 0; i < len; i++) {
        i2c_master_write_byte(cmd, i2cset_args.data->ival[i], ACK_CHECK_EN);
    }
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_port, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Write OK");
    } else if (ret == ESP_ERR_TIMEOUT) {
        ESP_LOGW(TAG, "Bus is busy");
    } else {
        ESP_LOGW(TAG, "Write Failed");
    }
    i2c_driver_delete(i2c_port);
    return 0;
}
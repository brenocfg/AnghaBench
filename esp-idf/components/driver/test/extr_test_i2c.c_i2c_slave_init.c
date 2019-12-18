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
struct TYPE_4__ {int /*<<< orphan*/  slave_addr; int /*<<< orphan*/  addr_10bit_en; } ;
struct TYPE_5__ {TYPE_1__ slave; int /*<<< orphan*/  scl_pullup_en; int /*<<< orphan*/  sda_pullup_en; int /*<<< orphan*/  scl_io_num; int /*<<< orphan*/  sda_io_num; int /*<<< orphan*/  mode; } ;
typedef  TYPE_2__ i2c_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_SLAVE_ADDR ; 
 int /*<<< orphan*/  GPIO_PULLUP_ENABLE ; 
 int /*<<< orphan*/  I2C_MODE_SLAVE ; 
 int /*<<< orphan*/  I2C_SLAVE_SCL_IO ; 
 int /*<<< orphan*/  I2C_SLAVE_SDA_IO ; 

__attribute__((used)) static i2c_config_t i2c_slave_init(void)
{
    i2c_config_t conf_slave = {
        .mode = I2C_MODE_SLAVE,
        .sda_io_num = I2C_SLAVE_SDA_IO,
        .scl_io_num = I2C_SLAVE_SCL_IO,
		.sda_pullup_en = GPIO_PULLUP_ENABLE,
	    .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .slave.addr_10bit_en = 0,
        .slave.slave_addr = ESP_SLAVE_ADDR,
    };
    return conf_slave;
}
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
struct TYPE_5__ {int /*<<< orphan*/  scl_io_num; int /*<<< orphan*/  sda_io_num; TYPE_1__ master; int /*<<< orphan*/  scl_pullup_en; int /*<<< orphan*/  sda_pullup_en; int /*<<< orphan*/  mode; } ;
typedef  TYPE_2__ i2c_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_PULLUP_ENABLE ; 
 int /*<<< orphan*/  I2C_MASTER_FREQ_HZ ; 
 int /*<<< orphan*/  I2C_MASTER_SCL_IO ; 
 int /*<<< orphan*/  I2C_MASTER_SDA_IO ; 
 int /*<<< orphan*/  I2C_MODE_MASTER ; 

__attribute__((used)) static i2c_config_t i2c_master_init(void)
{
    i2c_config_t conf_master = {
        .mode = I2C_MODE_MASTER,
		.sda_pullup_en = GPIO_PULLUP_ENABLE,
		.scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
    };
    return conf_master;
}
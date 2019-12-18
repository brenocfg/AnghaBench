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
struct tosa_lcd_data {int /*<<< orphan*/  i2c; struct spi_device* spi; scalar_t__ is_vga; } ;
struct spi_device {int dummy; } ;
struct i2c_board_info {char* type; struct spi_device* platform_data; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_BASE ; 
 int /*<<< orphan*/  TG_PINICTL ; 
 int /*<<< orphan*/  TG_PNLCTL ; 
 int TG_REG0_COLOR ; 
 int TG_REG0_LR ; 
 int TG_REG0_UD ; 
 int TG_REG0_VQV ; 
 struct i2c_adapter* i2c_get_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  tosa_tg_send (struct spi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tosa_lcd_tg_on(struct tosa_lcd_data *data)
{
	struct spi_device *spi = data->spi;
	int value = TG_REG0_COLOR | TG_REG0_UD | TG_REG0_LR;

	if (data->is_vga)
		value |= TG_REG0_VQV;

	tosa_tg_send(spi, TG_PNLCTL, value);

	/* TG LCD pannel power up */
	tosa_tg_send(spi, TG_PINICTL,0x4);
	mdelay(50);

	/* TG LCD GVSS */
	tosa_tg_send(spi, TG_PINICTL,0x0);

	if (!data->i2c) {
		/* after the pannel is powered up the first time, we can access the i2c bus */
		/* so probe for the DAC */
		struct i2c_adapter *adap = i2c_get_adapter(0);
		struct i2c_board_info info = {
			.type	= "tosa-bl",
			.addr	= DAC_BASE,
			.platform_data = data->spi,
		};
		data->i2c = i2c_new_device(adap, &info);
	}
}
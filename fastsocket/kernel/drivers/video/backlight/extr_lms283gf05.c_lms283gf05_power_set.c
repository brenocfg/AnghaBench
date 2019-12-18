#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct lms283gf05_pdata* platform_data; } ;
struct spi_device {TYPE_1__ dev; } ;
struct lms283gf05_state {struct spi_device* spi; } ;
struct lms283gf05_pdata {int /*<<< orphan*/  reset_inverted; int /*<<< orphan*/  reset_gpio; } ;
struct lcd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disp_initseq ; 
 int /*<<< orphan*/  disp_pdwnseq ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lms283gf05_state* lcd_get_data (struct lcd_device*) ; 
 int /*<<< orphan*/  lms283gf05_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lms283gf05_toggle (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lms283gf05_power_set(struct lcd_device *ld, int power)
{
	struct lms283gf05_state *st = lcd_get_data(ld);
	struct spi_device *spi = st->spi;
	struct lms283gf05_pdata *pdata = spi->dev.platform_data;

	if (power) {
		if (pdata)
			lms283gf05_reset(pdata->reset_gpio,
					pdata->reset_inverted);
		lms283gf05_toggle(spi, disp_initseq, ARRAY_SIZE(disp_initseq));
	} else {
		lms283gf05_toggle(spi, disp_pdwnseq, ARRAY_SIZE(disp_pdwnseq));
		if (pdata)
			gpio_set_value(pdata->reset_gpio,
					pdata->reset_inverted);
	}

	return 0;
}
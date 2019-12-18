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
struct device {int dummy; } ;
struct da903x_backlight_data {int id; int current_brightness; struct device* da903x_dev; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
#define  DA9030_ID_WLED 129 
 int /*<<< orphan*/  DA9030_WLED_CONTROL ; 
 int /*<<< orphan*/  DA9030_WLED_CP_EN ; 
 int /*<<< orphan*/  DA9030_WLED_TRIM (int) ; 
#define  DA9034_ID_WLED 128 
 int /*<<< orphan*/  DA9034_WLED_BOOST_EN ; 
 int /*<<< orphan*/  DA9034_WLED_CONTROL1 ; 
 int /*<<< orphan*/  DA9034_WLED_CONTROL2 ; 
 struct da903x_backlight_data* bl_get_data (struct backlight_device*) ; 
 int da903x_clr_bits (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int da903x_set_bits (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int da903x_update (struct device*,int /*<<< orphan*/ ,int,int) ; 
 int da903x_write (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da903x_backlight_set(struct backlight_device *bl, int brightness)
{
	struct da903x_backlight_data *data = bl_get_data(bl);
	struct device *dev = data->da903x_dev;
	uint8_t val;
	int ret = 0;

	switch (data->id) {
	case DA9034_ID_WLED:
		ret = da903x_update(dev, DA9034_WLED_CONTROL1,
				brightness, 0x7f);
		if (ret)
			return ret;

		if (data->current_brightness && brightness == 0)
			ret = da903x_clr_bits(dev,
					DA9034_WLED_CONTROL2,
					DA9034_WLED_BOOST_EN);

		if (data->current_brightness == 0 && brightness)
			ret = da903x_set_bits(dev,
					DA9034_WLED_CONTROL2,
					DA9034_WLED_BOOST_EN);
		break;
	case DA9030_ID_WLED:
		val = DA9030_WLED_TRIM(brightness);
		val |= brightness ? DA9030_WLED_CP_EN : 0;
		ret = da903x_write(dev, DA9030_WLED_CONTROL, val);
		break;
	}

	if (ret)
		return ret;

	data->current_brightness = brightness;
	return 0;
}
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
struct device {int dummy; } ;
struct backlight_device {int dummy; } ;
struct adp5520_bl {int /*<<< orphan*/  cached_daylight_max; struct adp5520_backlight_platfrom_data* pdata; struct device* master; } ;
struct adp5520_backlight_platfrom_data {int /*<<< orphan*/  fade_out; int /*<<< orphan*/  fade_in; scalar_t__ en_ambl_sens; int /*<<< orphan*/  fade_led_law; int /*<<< orphan*/  abml_filt; int /*<<< orphan*/  l3_hyst; int /*<<< orphan*/  l3_trip; int /*<<< orphan*/  l2_hyst; int /*<<< orphan*/  l2_trip; int /*<<< orphan*/  l3_dark_dim; int /*<<< orphan*/  l3_dark_max; int /*<<< orphan*/  l2_office_dim; int /*<<< orphan*/  l2_office_max; int /*<<< orphan*/  l1_daylight_max; int /*<<< orphan*/  l1_daylight_dim; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALS_CMPR_CFG ; 
 int /*<<< orphan*/  ALS_CMPR_CFG_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BL_CONTROL ; 
 int /*<<< orphan*/  BL_CTRL_VAL (int /*<<< orphan*/ ,scalar_t__) ; 
 int BL_EN ; 
 int /*<<< orphan*/  BL_FADE ; 
 int /*<<< orphan*/  DARK_DIM ; 
 int /*<<< orphan*/  DARK_MAX ; 
 int /*<<< orphan*/  DAYLIGHT_DIM ; 
 int /*<<< orphan*/  DAYLIGHT_MAX ; 
 int DIM_EN ; 
 int /*<<< orphan*/  FADE_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2_HYS ; 
 int /*<<< orphan*/  L2_TRIP ; 
 int /*<<< orphan*/  L3_EN ; 
 int /*<<< orphan*/  L3_HYS ; 
 int /*<<< orphan*/  L3_TRIP ; 
 int /*<<< orphan*/  MODE_STATUS ; 
 int /*<<< orphan*/  OFFICE_DIM ; 
 int /*<<< orphan*/  OFFICE_MAX ; 
 int adp5520_set_bits (struct device*,int /*<<< orphan*/ ,int) ; 
 int adp5520_write (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adp5520_bl* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int adp5520_bl_setup(struct backlight_device *bl)
{
	struct adp5520_bl *data = bl_get_data(bl);
	struct device *master = data->master;
	struct adp5520_backlight_platfrom_data *pdata = data->pdata;
	int ret = 0;

	ret |= adp5520_write(master, DAYLIGHT_MAX, pdata->l1_daylight_max);
	ret |= adp5520_write(master, DAYLIGHT_DIM, pdata->l1_daylight_dim);

	if (pdata->en_ambl_sens) {
		data->cached_daylight_max = pdata->l1_daylight_max;
		ret |= adp5520_write(master, OFFICE_MAX, pdata->l2_office_max);
		ret |= adp5520_write(master, OFFICE_DIM, pdata->l2_office_dim);
		ret |= adp5520_write(master, DARK_MAX, pdata->l3_dark_max);
		ret |= adp5520_write(master, DARK_DIM, pdata->l3_dark_dim);
		ret |= adp5520_write(master, L2_TRIP, pdata->l2_trip);
		ret |= adp5520_write(master, L2_HYS, pdata->l2_hyst);
		ret |= adp5520_write(master, L3_TRIP, pdata->l3_trip);
		ret |= adp5520_write(master, L3_HYS, pdata->l3_hyst);
		ret |= adp5520_write(master, ALS_CMPR_CFG,
			ALS_CMPR_CFG_VAL(pdata->abml_filt, L3_EN));
	}

	ret |= adp5520_write(master, BL_CONTROL,
			BL_CTRL_VAL(pdata->fade_led_law, pdata->en_ambl_sens));

	ret |= adp5520_write(master, BL_FADE, FADE_VAL(pdata->fade_in,
			pdata->fade_out));

	ret |= adp5520_set_bits(master, MODE_STATUS, BL_EN | DIM_EN);

	return ret;
}
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
struct ds2760_device_info {scalar_t__ update_time; int* raw; int voltage_raw; int voltage_uV; char current_raw; int current_uA; char accum_current_raw; int accum_current_uAh; char temp_raw; int temp_C; int rated_capacity; int full_active_uAh; int empty_uAh; long rem_capacity; long life_sec; int /*<<< orphan*/  w1_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int DS2760_ACTIVE_EMPTY ; 
 size_t DS2760_ACTIVE_FULL ; 
 size_t DS2760_CURRENT_ACCUM_LSB ; 
 size_t DS2760_CURRENT_ACCUM_MSB ; 
 size_t DS2760_CURRENT_LSB ; 
 size_t DS2760_CURRENT_MSB ; 
 int DS2760_DATA_SIZE ; 
 size_t DS2760_RATED_CAPACITY ; 
 int DS2760_TEMP_LSB ; 
 size_t DS2760_TEMP_MSB ; 
 size_t DS2760_VOLTAGE_LSB ; 
 size_t DS2760_VOLTAGE_MSB ; 
 void* battery_interpolate (int*,int) ; 
 int /*<<< orphan*/  cache_time ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int* rated_capacities ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 
 int w1_ds2760_read (int /*<<< orphan*/ ,int*,int,int) ; 

__attribute__((used)) static int ds2760_battery_read_status(struct ds2760_device_info *di)
{
	int ret, i, start, count, scale[5];

	if (di->update_time && time_before(jiffies, di->update_time +
					   msecs_to_jiffies(cache_time)))
		return 0;

	/* The first time we read the entire contents of SRAM/EEPROM,
	 * but after that we just read the interesting bits that change. */
	if (di->update_time == 0) {
		start = 0;
		count = DS2760_DATA_SIZE;
	} else {
		start = DS2760_VOLTAGE_MSB;
		count = DS2760_TEMP_LSB - start + 1;
	}

	ret = w1_ds2760_read(di->w1_dev, di->raw + start, start, count);
	if (ret != count) {
		dev_warn(di->dev, "call to w1_ds2760_read failed (0x%p)\n",
			 di->w1_dev);
		return 1;
	}

	di->update_time = jiffies;

	/* DS2760 reports voltage in units of 4.88mV, but the battery class
	 * reports in units of uV, so convert by multiplying by 4880. */
	di->voltage_raw = (di->raw[DS2760_VOLTAGE_MSB] << 3) |
			  (di->raw[DS2760_VOLTAGE_LSB] >> 5);
	di->voltage_uV = di->voltage_raw * 4880;

	/* DS2760 reports current in signed units of 0.625mA, but the battery
	 * class reports in units of µA, so convert by multiplying by 625. */
	di->current_raw =
	    (((signed char)di->raw[DS2760_CURRENT_MSB]) << 5) |
			  (di->raw[DS2760_CURRENT_LSB] >> 3);
	di->current_uA = di->current_raw * 625;

	/* DS2760 reports accumulated current in signed units of 0.25mAh. */
	di->accum_current_raw =
	    (((signed char)di->raw[DS2760_CURRENT_ACCUM_MSB]) << 8) |
			   di->raw[DS2760_CURRENT_ACCUM_LSB];
	di->accum_current_uAh = di->accum_current_raw * 250;

	/* DS2760 reports temperature in signed units of 0.125°C, but the
	 * battery class reports in units of 1/10 °C, so we convert by
	 * multiplying by .125 * 10 = 1.25. */
	di->temp_raw = (((signed char)di->raw[DS2760_TEMP_MSB]) << 3) |
				     (di->raw[DS2760_TEMP_LSB] >> 5);
	di->temp_C = di->temp_raw + (di->temp_raw / 4);

	/* At least some battery monitors (e.g. HP iPAQ) store the battery's
	 * maximum rated capacity. */
	if (di->raw[DS2760_RATED_CAPACITY] < ARRAY_SIZE(rated_capacities))
		di->rated_capacity = rated_capacities[
			(unsigned int)di->raw[DS2760_RATED_CAPACITY]];
	else
		di->rated_capacity = di->raw[DS2760_RATED_CAPACITY] * 10;

	di->rated_capacity *= 1000; /* convert to µAh */

	/* Calculate the full level at the present temperature. */
	di->full_active_uAh = di->raw[DS2760_ACTIVE_FULL] << 8 |
			      di->raw[DS2760_ACTIVE_FULL + 1];

	/* If the full_active_uAh value is not given, fall back to the rated
	 * capacity. This is likely to happen when chips are not part of the
	 * battery pack and is therefore not bootstrapped. */
	if (di->full_active_uAh == 0)
		di->full_active_uAh = di->rated_capacity / 1000L;

	scale[0] = di->full_active_uAh;
	for (i = 1; i < 5; i++)
		scale[i] = scale[i - 1] + di->raw[DS2760_ACTIVE_FULL + 2 + i];

	di->full_active_uAh = battery_interpolate(scale, di->temp_C / 10);
	di->full_active_uAh *= 1000; /* convert to µAh */

	/* Calculate the empty level at the present temperature. */
	scale[4] = di->raw[DS2760_ACTIVE_EMPTY + 4];
	for (i = 3; i >= 0; i--)
		scale[i] = scale[i + 1] + di->raw[DS2760_ACTIVE_EMPTY + i];

	di->empty_uAh = battery_interpolate(scale, di->temp_C / 10);
	di->empty_uAh *= 1000; /* convert to µAh */

	if (di->full_active_uAh == di->empty_uAh)
		di->rem_capacity = 0;
	else
		/* From Maxim Application Note 131: remaining capacity =
		 * ((ICA - Empty Value) / (Full Value - Empty Value)) x 100% */
		di->rem_capacity = ((di->accum_current_uAh - di->empty_uAh) * 100L) /
				    (di->full_active_uAh - di->empty_uAh);

	if (di->rem_capacity < 0)
		di->rem_capacity = 0;
	if (di->rem_capacity > 100)
		di->rem_capacity = 100;

	if (di->current_uA >= 100L)
		di->life_sec = -((di->accum_current_uAh - di->empty_uAh) * 36L)
					/ (di->current_uA / 100L);
	else
		di->life_sec = 0;

	return 0;
}
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
typedef  size_t u8 ;
struct zd_chip {size_t* pwr_int_values; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RF_RV_BITS ; 
 int /*<<< orphan*/  UW2453_REGWRITE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,size_t,int) ; 
 int /*<<< orphan*/ * uw2453_txgain ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_rfwrite_locked (struct zd_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uw2453_set_tx_gain_level(struct zd_chip *chip, int channel)
{
	u8 int_value = chip->pwr_int_values[channel - 1];

	if (int_value >= ARRAY_SIZE(uw2453_txgain)) {
		dev_dbg_f(zd_chip_dev(chip), "can't configure TX gain for "
			  "int value %x on channel %d\n", int_value, channel);
		return 0;
	}

	return zd_rfwrite_locked(chip,
		UW2453_REGWRITE(7, uw2453_txgain[int_value]), RF_RV_BITS);
}
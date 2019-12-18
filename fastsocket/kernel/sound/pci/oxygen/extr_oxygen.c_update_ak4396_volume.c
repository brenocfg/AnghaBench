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
struct oxygen {int /*<<< orphan*/ * dac_volume; struct generic_data* model_data; } ;
struct generic_data {unsigned int dacs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4396_LCH_ATT ; 
 int /*<<< orphan*/  AK4396_RCH_ATT ; 
 int /*<<< orphan*/  ak4396_write_cached (struct oxygen*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_ak4396_volume(struct oxygen *chip)
{
	struct generic_data *data = chip->model_data;
	unsigned int i;

	for (i = 0; i < data->dacs; ++i) {
		ak4396_write_cached(chip, i, AK4396_LCH_ATT,
				    chip->dac_volume[i * 2]);
		ak4396_write_cached(chip, i, AK4396_RCH_ATT,
				    chip->dac_volume[i * 2 + 1]);
	}
}
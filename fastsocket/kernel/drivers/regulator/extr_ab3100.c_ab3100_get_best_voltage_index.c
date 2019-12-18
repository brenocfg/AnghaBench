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
struct regulator_dev {int /*<<< orphan*/  dev; struct ab3100_regulator* reg_data; } ;
struct ab3100_regulator {int voltages_len; int* typ_voltages; } ;

/* Variables and functions */
 int EINVAL ; 
 int INT_MAX ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static int ab3100_get_best_voltage_index(struct regulator_dev *reg,
				   int min_uV, int max_uV)
{
	struct ab3100_regulator *abreg = reg->reg_data;
	int i;
	int bestmatch;
	int bestindex;

	/*
	 * Locate the minimum voltage fitting the criteria on
	 * this regulator. The switchable voltages are not
	 * in strict falling order so we need to check them
	 * all for the best match.
	 */
	bestmatch = INT_MAX;
	bestindex = -1;
	for (i = 0; i < abreg->voltages_len; i++) {
		if (abreg->typ_voltages[i] <= max_uV &&
		    abreg->typ_voltages[i] >= min_uV &&
		    abreg->typ_voltages[i] < bestmatch) {
			bestmatch = abreg->typ_voltages[i];
			bestindex = i;
		}
	}

	if (bestindex < 0) {
		dev_warn(&reg->dev, "requested %d<=x<=%d uV, out of range!\n",
			 min_uV, max_uV);
		return -EINVAL;
	}
	return bestindex;
}
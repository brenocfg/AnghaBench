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
struct ipath_devdata {int ipath_i2c_chain_type; } ;
struct i2c_chain_desc {scalar_t__ probe_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct i2c_chain_desc*) ; 
 scalar_t__ IPATH_NO_DEV ; 
 int /*<<< orphan*/  eeprom_reset (struct ipath_devdata*) ; 
 struct i2c_chain_desc* i2c_chains ; 
 int /*<<< orphan*/  i2c_probe (struct ipath_devdata*,scalar_t__) ; 

__attribute__((used)) static struct i2c_chain_desc *ipath_i2c_type(struct ipath_devdata *dd)
{
	int idx;

	/* Get memoized index, from previous successful probes */
	idx = dd->ipath_i2c_chain_type - 1;
	if (idx >= 0 && idx < (ARRAY_SIZE(i2c_chains) - 1))
		goto done;

	idx = 0;
	while (i2c_chains[idx].probe_dev != IPATH_NO_DEV) {
		/* if probe succeeds, this is type */
		if (!i2c_probe(dd, i2c_chains[idx].probe_dev))
			break;
		++idx;
	}

	/*
	 * Old EEPROM (first entry) may require a reset after probe,
	 * rather than being able to "start" after "stop"
	 */
	if (idx == 0)
		eeprom_reset(dd);

	if (i2c_chains[idx].probe_dev == IPATH_NO_DEV)
		idx = -1;
	else
		dd->ipath_i2c_chain_type = idx + 1;
done:
	return (idx >= 0) ? i2c_chains + idx : NULL;
}
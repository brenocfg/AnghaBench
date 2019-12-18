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
struct bq27x00_device_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ27x00_REG_RSOC ; 
 int bq27x00_read (int /*<<< orphan*/ ,int*,int,struct bq27x00_device_info*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int bq27x00_battery_rsoc(struct bq27x00_device_info *di)
{
	int ret;
	int rsoc = 0;

	ret = bq27x00_read(BQ27x00_REG_RSOC, &rsoc, 1, di);
	if (ret) {
		dev_err(di->dev, "error reading relative State-of-Charge\n");
		return ret;
	}

	return rsoc >> 8;
}
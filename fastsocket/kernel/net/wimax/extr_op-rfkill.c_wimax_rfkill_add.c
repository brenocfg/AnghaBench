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
struct wimax_dev {struct rfkill* rfkill; int /*<<< orphan*/  rf_sw; int /*<<< orphan*/ * op_rfkill_sw_toggle; int /*<<< orphan*/  name; } ;
struct rfkill {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RFKILL_TYPE_WIMAX ; 
 int /*<<< orphan*/  WIMAX_RF_ON ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct wimax_dev*,...) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct wimax_dev*) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,struct rfkill*) ; 
 struct rfkill* rfkill_alloc (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct wimax_dev*) ; 
 int /*<<< orphan*/  rfkill_destroy (struct rfkill*) ; 
 int rfkill_register (struct rfkill*) ; 
 struct device* wimax_dev_to_dev (struct wimax_dev*) ; 
 int /*<<< orphan*/  wimax_rfkill_ops ; 

int wimax_rfkill_add(struct wimax_dev *wimax_dev)
{
	int result;
	struct rfkill *rfkill;
	struct device *dev = wimax_dev_to_dev(wimax_dev);

	d_fnstart(3, dev, "(wimax_dev %p)\n", wimax_dev);
	/* Initialize RF Kill */
	result = -ENOMEM;
	rfkill = rfkill_alloc(wimax_dev->name, dev, RFKILL_TYPE_WIMAX,
			      &wimax_rfkill_ops, wimax_dev);
	if (rfkill == NULL)
		goto error_rfkill_allocate;

	d_printf(1, dev, "rfkill %p\n", rfkill);

	wimax_dev->rfkill = rfkill;

	result = rfkill_register(wimax_dev->rfkill);
	if (result < 0)
		goto error_rfkill_register;

	/* If there is no SW toggle op, SW RFKill is always on */
	if (wimax_dev->op_rfkill_sw_toggle == NULL)
		wimax_dev->rf_sw = WIMAX_RF_ON;

	d_fnend(3, dev, "(wimax_dev %p) = 0\n", wimax_dev);
	return 0;

error_rfkill_register:
	rfkill_destroy(wimax_dev->rfkill);
error_rfkill_allocate:
	d_fnend(3, dev, "(wimax_dev %p) = %d\n", wimax_dev, result);
	return result;
}
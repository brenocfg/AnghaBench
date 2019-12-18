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
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  uwb_dbg_add_rc (struct uwb_rc*) ; 
 int uwb_radio_setup (struct uwb_rc*) ; 
 int uwb_rc_dev_addr_assign (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rc_ie_release (struct uwb_rc*) ; 
 int uwb_rc_ie_setup (struct uwb_rc*) ; 
 int uwb_rc_mac_addr_setup (struct uwb_rc*) ; 
 int uwb_rsv_setup (struct uwb_rc*) ; 

__attribute__((used)) static int uwb_rc_setup(struct uwb_rc *rc)
{
	int result;
	struct device *dev = &rc->uwb_dev.dev;

	result = uwb_radio_setup(rc);
	if (result < 0) {
		dev_err(dev, "cannot setup UWB radio: %d\n", result);
		goto error;
	}
	result = uwb_rc_mac_addr_setup(rc);
	if (result < 0) {
		dev_err(dev, "cannot setup UWB MAC address: %d\n", result);
		goto error;
	}
	result = uwb_rc_dev_addr_assign(rc);
	if (result < 0) {
		dev_err(dev, "cannot assign UWB DevAddr: %d\n", result);
		goto error;
	}
	result = uwb_rc_ie_setup(rc);
	if (result < 0) {
		dev_err(dev, "cannot setup IE subsystem: %d\n", result);
		goto error_ie_setup;
	}
	result = uwb_rsv_setup(rc);
	if (result < 0) {
		dev_err(dev, "cannot setup reservation subsystem: %d\n", result);
		goto error_rsv_setup;
	}
	uwb_dbg_add_rc(rc);
	return 0;

error_rsv_setup:
	uwb_rc_ie_release(rc);
error_ie_setup:
error:
	return result;
}
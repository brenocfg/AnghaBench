#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct usb_interface {struct device dev; } ;
struct usb_device {scalar_t__ auto_pm; } ;
struct i2400m {scalar_t__ updown; scalar_t__ state; } ;
struct i2400mu {int /*<<< orphan*/  do_autopm; struct i2400m i2400m; struct usb_device* usb_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ pm_message_t ;

/* Variables and functions */
 int EBADF ; 
 scalar_t__ I2400M_SS_DATA_PATH_CONNECTED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct usb_interface*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct usb_interface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int i2400m_cmd_enter_powersave (struct i2400m*) ; 
 int /*<<< orphan*/  i2400mu_notification_release (struct i2400mu*) ; 
 struct i2400mu* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static
int i2400mu_suspend(struct usb_interface *iface, pm_message_t pm_msg)
{
	int result = 0;
	struct device *dev = &iface->dev;
	struct i2400mu *i2400mu = usb_get_intfdata(iface);
#ifdef CONFIG_PM
	struct usb_device *usb_dev = i2400mu->usb_dev;
#endif
	unsigned is_autosuspend = 0;
	struct i2400m *i2400m = &i2400mu->i2400m;

#ifdef CONFIG_PM
	if (usb_dev->auto_pm > 0)
		is_autosuspend = 1;
#endif

	d_fnstart(3, dev, "(iface %p pm_msg %u)\n", iface, pm_msg.event);
	if (i2400m->updown == 0)
		goto no_firmware;
	if (i2400m->state == I2400M_SS_DATA_PATH_CONNECTED && is_autosuspend) {
		/* ugh -- the device is connected and this suspend
		 * request is an autosuspend one (not a system standby
		 * / hibernate).
		 *
		 * The only way the device can go to standby is if the
		 * link with the base station is in IDLE mode; that
		 * were the case, we'd be in status
		 * I2400M_SS_CONNECTED_IDLE. But we are not.
		 *
		 * If we *tell* him to go power save now, it'll reset
		 * as a precautionary measure, so if this is an
		 * autosuspend thing, say no and it'll come back
		 * later, when the link is IDLE
		 */
		result = -EBADF;
		d_printf(1, dev, "fw up, link up, not-idle, autosuspend: "
			 "not entering powersave\n");
		goto error_not_now;
	}
	d_printf(1, dev, "fw up: entering powersave\n");
	atomic_dec(&i2400mu->do_autopm);
	result = i2400m_cmd_enter_powersave(i2400m);
	atomic_inc(&i2400mu->do_autopm);
	if (result < 0 && !is_autosuspend) {
		/* System suspend, can't fail */
		dev_err(dev, "failed to suspend, will reset on resume\n");
		result = 0;
	}
	if (result < 0)
		goto error_enter_powersave;
	i2400mu_notification_release(i2400mu);
	d_printf(1, dev, "powersave requested\n");
error_enter_powersave:
error_not_now:
no_firmware:
	d_fnend(3, dev, "(iface %p pm_msg %u) = %d\n",
		iface, pm_msg.event, result);
	return result;
}
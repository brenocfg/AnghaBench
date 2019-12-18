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
typedef  scalar_t__ u64 ;
struct device {int dummy; } ;
struct sdio_func {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ETIME ; 
 int HZ ; 
 int /*<<< orphan*/  I2400MS_INIT_SLEEP_INTERVAL ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct sdio_func*,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct sdio_func*) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ get_jiffies_64 () ; 
 int ioe_timeout ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 int sdio_enable_func (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 scalar_t__ time_before64 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static
int i2400ms_enable_function(struct sdio_func *func)
{
	u64 timeout;
	int err;
	struct device *dev = &func->dev;

	d_fnstart(3, dev, "(func %p)\n", func);
	/* Setup timeout (FIXME: This needs to read the CIS table to
	 * get a real timeout) and then wait for the device to signal
	 * it is ready */
	timeout = get_jiffies_64() + ioe_timeout * HZ;
	err = -ENODEV;
	while (err != 0 && time_before64(get_jiffies_64(), timeout)) {
		sdio_claim_host(func);
		err = sdio_enable_func(func);
		if (0 == err) {
			sdio_release_host(func);
			d_printf(2, dev, "SDIO function enabled\n");
			goto function_enabled;
		}
		d_printf(2, dev, "SDIO function failed to enable: %d\n", err);
		sdio_disable_func(func);
		sdio_release_host(func);
		msleep(I2400MS_INIT_SLEEP_INTERVAL);
	}
	/* If timed out, device is not there yet -- get -ENODEV so
	 * the device driver core will retry later on. */
	if (err == -ETIME) {
		dev_err(dev, "Can't enable WiMAX function; "
			" has the function been enabled?\n");
		err = -ENODEV;
	}
function_enabled:
	d_fnend(3, dev, "(func %p) = %d\n", func, err);
	return err;
}
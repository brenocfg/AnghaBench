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
struct wimax_dev {int /*<<< orphan*/  name; } ;
struct i2400m {struct wimax_dev wimax_dev; } ;
struct i2400mu {int /*<<< orphan*/  rx_kthread; TYPE_1__* usb_iface; struct i2400m i2400m; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  i2400mu_rxd ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct i2400mu*,char*,int /*<<< orphan*/ ) ; 

int i2400mu_rx_setup(struct i2400mu *i2400mu)
{
	int result = 0;
	struct i2400m *i2400m = &i2400mu->i2400m;
	struct device *dev = &i2400mu->usb_iface->dev;
	struct wimax_dev *wimax_dev = &i2400m->wimax_dev;

	i2400mu->rx_kthread = kthread_run(i2400mu_rxd, i2400mu, "%s-rx",
					  wimax_dev->name);
	if (IS_ERR(i2400mu->rx_kthread)) {
		result = PTR_ERR(i2400mu->rx_kthread);
		dev_err(dev, "RX: cannot start thread: %d\n", result);
	}
	return result;
}
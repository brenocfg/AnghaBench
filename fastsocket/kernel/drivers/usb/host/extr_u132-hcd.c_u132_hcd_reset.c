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
struct usb_hcd {int dummy; } ;
struct u132 {int going; int /*<<< orphan*/  sw_lock; TYPE_1__* platform_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct u132* hcd_to_u132 (struct usb_hcd*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u132_disable (struct u132*) ; 
 int u132_init (struct u132*) ; 

__attribute__((used)) static int u132_hcd_reset(struct usb_hcd *hcd)
{
	struct u132 *u132 = hcd_to_u132(hcd);
	if (u132->going > 1) {
		dev_err(&u132->platform_dev->dev, "device has been removed %d\n"
			, u132->going);
		return -ENODEV;
	} else if (u132->going > 0) {
		dev_err(&u132->platform_dev->dev, "device is being removed\n");
		return -ESHUTDOWN;
	} else {
		int retval;
		mutex_lock(&u132->sw_lock);
		retval = u132_init(u132);
		if (retval) {
			u132_disable(u132);
			u132->going = 1;
		}
		mutex_unlock(&u132->sw_lock);
		return retval;
	}
}
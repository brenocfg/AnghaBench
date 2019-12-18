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
struct rc_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  kfree (struct rc_dev*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct rc_dev* to_rc_dev (struct device*) ; 

__attribute__((used)) static void rc_dev_release(struct device *device)
{
	struct rc_dev *dev = to_rc_dev(device);

	kfree(dev);
	module_put(THIS_MODULE);
}
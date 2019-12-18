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
struct uwb_rc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __uwb_rc_get (struct uwb_rc*) ; 
 struct device* class_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct uwb_rc*,int /*<<< orphan*/ ) ; 
 struct uwb_rc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  find_rc_try_get ; 
 int /*<<< orphan*/  uwb_rc_class ; 

struct uwb_rc *__uwb_rc_try_get(struct uwb_rc *target_rc)
{
	struct device *dev;
	struct uwb_rc *rc = NULL;

	dev = class_find_device(&uwb_rc_class, NULL, target_rc,
				find_rc_try_get);
	if (dev) {
		rc = dev_get_drvdata(dev);
		__uwb_rc_get(rc);
	}
	return rc;
}
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
struct expansion_card {scalar_t__ loader; scalar_t__ claimed; } ;
struct ecard_request {struct expansion_card* ec; int /*<<< orphan*/  fn; } ;
struct ecard_driver {int /*<<< orphan*/  (* shutdown ) (struct expansion_card*) ;} ;
struct device {scalar_t__ driver; } ;

/* Variables and functions */
 struct expansion_card* ECARD_DEV (struct device*) ; 
 struct ecard_driver* ECARD_DRV (scalar_t__) ; 
 int /*<<< orphan*/  ecard_call (struct ecard_request*) ; 
 int /*<<< orphan*/  ecard_task_reset ; 
 int /*<<< orphan*/  stub1 (struct expansion_card*) ; 

__attribute__((used)) static void ecard_drv_shutdown(struct device *dev)
{
	struct expansion_card *ec = ECARD_DEV(dev);
	struct ecard_driver *drv = ECARD_DRV(dev->driver);
	struct ecard_request req;

	if (dev->driver) {
		if (drv->shutdown)
			drv->shutdown(ec);
		ec->claimed = 0;
	}

	/*
	 * If this card has a loader, call the reset handler.
	 */
	if (ec->loader) {
		req.fn = ecard_task_reset;
		req.ec = ec;
		ecard_call(&req);
	}
}
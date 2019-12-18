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
struct TYPE_2__ {int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 int class_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_unregister (int /*<<< orphan*/ *) ; 
 int driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpsb_register_highlevel (int /*<<< orphan*/ *) ; 
 TYPE_1__ nodemgr_dev_template_host ; 
 int /*<<< orphan*/  nodemgr_highlevel ; 
 int /*<<< orphan*/  nodemgr_mid_layer_driver ; 
 int /*<<< orphan*/  nodemgr_ne_class ; 
 int /*<<< orphan*/  nodemgr_ud_class ; 

int init_ieee1394_nodemgr(void)
{
	int error;

	error = class_register(&nodemgr_ne_class);
	if (error)
		goto fail_ne;
	error = class_register(&nodemgr_ud_class);
	if (error)
		goto fail_ud;
	error = driver_register(&nodemgr_mid_layer_driver);
	if (error)
		goto fail_ml;
	/* This driver is not used if nodemgr is off (disable_nodemgr=1). */
	nodemgr_dev_template_host.driver = &nodemgr_mid_layer_driver;

	hpsb_register_highlevel(&nodemgr_highlevel);
	return 0;

fail_ml:
	class_unregister(&nodemgr_ud_class);
fail_ud:
	class_unregister(&nodemgr_ne_class);
fail_ne:
	return error;
}
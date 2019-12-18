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

/* Variables and functions */
 int /*<<< orphan*/  class_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpsb_unregister_highlevel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nodemgr_highlevel ; 
 int /*<<< orphan*/  nodemgr_mid_layer_driver ; 
 int /*<<< orphan*/  nodemgr_ne_class ; 
 int /*<<< orphan*/  nodemgr_ud_class ; 

void cleanup_ieee1394_nodemgr(void)
{
	hpsb_unregister_highlevel(&nodemgr_highlevel);
	driver_unregister(&nodemgr_mid_layer_driver);
	class_unregister(&nodemgr_ud_class);
	class_unregister(&nodemgr_ne_class);
}
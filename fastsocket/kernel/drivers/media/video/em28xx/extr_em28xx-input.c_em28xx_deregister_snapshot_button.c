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
struct em28xx {int /*<<< orphan*/ * sbutton_input_dev; int /*<<< orphan*/  sbutton_query_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_rearming_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  em28xx_info (char*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 

void em28xx_deregister_snapshot_button(struct em28xx *dev)
{
	if (dev->sbutton_input_dev != NULL) {
		em28xx_info("Deregistering snapshot button\n");
		cancel_rearming_delayed_work(&dev->sbutton_query_work);
		input_unregister_device(dev->sbutton_input_dev);
		dev->sbutton_input_dev = NULL;
	}
	return;
}
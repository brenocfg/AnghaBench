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
struct backing_dev_info {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bdi_cap_flush_forker (struct backing_dev_info*) ; 
 int /*<<< orphan*/  bdi_debug_unregister (struct backing_dev_info*) ; 
 int /*<<< orphan*/  bdi_prune_sb (struct backing_dev_info*) ; 
 int /*<<< orphan*/  bdi_wb_shutdown (struct backing_dev_info*) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_writeback_bdi_unregister (struct backing_dev_info*) ; 

void bdi_unregister(struct backing_dev_info *bdi)
{
	if (bdi->dev) {
		trace_writeback_bdi_unregister(bdi);
		bdi_prune_sb(bdi);

		if (!bdi_cap_flush_forker(bdi))
			bdi_wb_shutdown(bdi);
		bdi_debug_unregister(bdi);
		device_unregister(bdi->dev);
		bdi->dev = NULL;
	}
}
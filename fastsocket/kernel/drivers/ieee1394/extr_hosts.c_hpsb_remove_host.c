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
struct hpsb_host {int is_shutdown; int /*<<< orphan*/  device; int /*<<< orphan*/  host_dev; int /*<<< orphan*/ * driver; int /*<<< orphan*/  delayed_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dummy_driver ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  highlevel_remove_host (struct hpsb_host*) ; 

void hpsb_remove_host(struct hpsb_host *host)
{
	host->is_shutdown = 1;

	cancel_delayed_work(&host->delayed_reset);
	flush_scheduled_work();

	host->driver = &dummy_driver;
	highlevel_remove_host(host);

	device_unregister(&host->host_dev);
	device_unregister(&host->device);
}
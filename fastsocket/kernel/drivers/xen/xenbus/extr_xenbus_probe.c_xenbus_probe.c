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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe_watch ; 
 int /*<<< orphan*/  register_xenbus_watch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_backend_probe_and_watch () ; 
 int /*<<< orphan*/  xenbus_frontend ; 
 int /*<<< orphan*/  xenbus_probe_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenstore_chain ; 
 scalar_t__ xenstored_ready ; 

void xenbus_probe(struct work_struct *unused)
{
	BUG_ON((xenstored_ready <= 0));

	/* Enumerate devices in xenstore and watch for changes. */
	xenbus_probe_devices(&xenbus_frontend);
	register_xenbus_watch(&fe_watch);
	xenbus_backend_probe_and_watch();

	/* Notify others that xenstore is up */
	blocking_notifier_call_chain(&xenstore_chain, 0, NULL);
}
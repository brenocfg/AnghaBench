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
struct net_device {int dummy; } ;
struct lapb_cb {int dummy; } ;

/* Variables and functions */
 int LAPB_BADTOKEN ; 
 int LAPB_OK ; 
 struct lapb_cb* __lapb_devtostruct (struct net_device*) ; 
 int /*<<< orphan*/  __lapb_remove_cb (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_clear_queues (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_list_lock ; 
 int /*<<< orphan*/  lapb_put (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_stop_t1timer (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_stop_t2timer (struct lapb_cb*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int lapb_unregister(struct net_device *dev)
{
	struct lapb_cb *lapb;
	int rc = LAPB_BADTOKEN;

	write_lock_bh(&lapb_list_lock);
	lapb = __lapb_devtostruct(dev);
	if (!lapb)
		goto out;

	lapb_stop_t1timer(lapb);
	lapb_stop_t2timer(lapb);

	lapb_clear_queues(lapb);

	__lapb_remove_cb(lapb);

	lapb_put(lapb);
	rc = LAPB_OK;
out:
	write_unlock_bh(&lapb_list_lock);
	return rc;
}
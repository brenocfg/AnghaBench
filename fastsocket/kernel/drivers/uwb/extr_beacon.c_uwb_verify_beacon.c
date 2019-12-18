#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uwb_rc_evt_beacon {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;
struct TYPE_4__ {int size; } ;
struct uwb_event {TYPE_2__ notif; } ;
struct uwb_beacon_frame {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 

__attribute__((used)) static int uwb_verify_beacon(struct uwb_rc *rc, struct uwb_event *evt,
			     struct uwb_rc_evt_beacon *be)
{
	int result = -EINVAL;
	struct uwb_beacon_frame *bf;
	struct device *dev = &rc->uwb_dev.dev;

	/* Is there enough data to decode a beacon frame? */
	if (evt->notif.size < sizeof(*be) + sizeof(*bf)) {
		dev_err(dev, "BEACON event: Not enough data to decode "
			"(%zu vs %zu bytes needed)\n", evt->notif.size,
			sizeof(*be) + sizeof(*bf));
		goto error;
	}
	/* FIXME: make sure beacon frame IEs are fine and that the whole thing
	 * is consistent */
	result = 0;
error:
	return result;
}
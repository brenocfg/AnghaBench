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
struct ib_device_attr {int /*<<< orphan*/  local_ca_ack_delay; } ;
struct cm_device {int /*<<< orphan*/  ack_delay; int /*<<< orphan*/  ib_device; } ;

/* Variables and functions */
 scalar_t__ ib_query_device (int /*<<< orphan*/ ,struct ib_device_attr*) ; 

__attribute__((used)) static void cm_get_ack_delay(struct cm_device *cm_dev)
{
	struct ib_device_attr attr;

	if (ib_query_device(cm_dev->ib_device, &attr))
		cm_dev->ack_delay = 0; /* acks will rely on packet life time */
	else
		cm_dev->ack_delay = attr.local_ca_ack_delay;
}
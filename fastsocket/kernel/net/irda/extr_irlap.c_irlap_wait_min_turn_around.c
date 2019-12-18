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
struct TYPE_4__ {int value; } ;
struct TYPE_3__ {int value; } ;
struct qos_info {TYPE_2__ min_turn_time; TYPE_1__ baud_rate; } ;
struct irlap_cb {int mtt_required; int /*<<< orphan*/  xbofs_delay; } ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  irlap_min_turn_time_in_bytes (int,int) ; 

void irlap_wait_min_turn_around(struct irlap_cb *self, struct qos_info *qos)
{
	__u32 min_turn_time;
	__u32 speed;

	/* Get QoS values.  */
	speed = qos->baud_rate.value;
	min_turn_time = qos->min_turn_time.value;

	/* No need to calculate XBOFs for speeds over 115200 bps */
	if (speed > 115200) {
		self->mtt_required = min_turn_time;
		return;
	}

	/*
	 *  Send additional BOF's for the next frame for the requested
	 *  min turn time, so now we must calculate how many chars (XBOF's) we
	 *  must send for the requested time period (min turn time)
	 */
	self->xbofs_delay = irlap_min_turn_time_in_bytes(speed, min_turn_time);
}
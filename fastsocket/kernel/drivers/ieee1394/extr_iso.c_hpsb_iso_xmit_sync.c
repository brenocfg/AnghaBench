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
struct hpsb_iso {scalar_t__ type; scalar_t__ buf_packets; int /*<<< orphan*/  waitq; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HPSB_ISO_XMIT ; 
 scalar_t__ hpsb_iso_n_ready (struct hpsb_iso*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int hpsb_iso_xmit_sync(struct hpsb_iso *iso)
{
	if (iso->type != HPSB_ISO_XMIT)
		return -EINVAL;

	return wait_event_interruptible(iso->waitq,
					hpsb_iso_n_ready(iso) ==
					iso->buf_packets);
}
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
typedef  int /*<<< orphan*/  u64 ;
struct hpsb_iso {scalar_t__ type; int channel; TYPE_2__* host; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int (* isoctl ) (struct hpsb_iso*,int /*<<< orphan*/ ,unsigned long) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HPSB_ISO_RECV ; 
 int /*<<< orphan*/  RECV_SET_CHANNEL_MASK ; 
 int stub1 (struct hpsb_iso*,int /*<<< orphan*/ ,unsigned long) ; 

int hpsb_iso_recv_set_channel_mask(struct hpsb_iso *iso, u64 mask)
{
	if (iso->type != HPSB_ISO_RECV || iso->channel != -1)
		return -EINVAL;
	return iso->host->driver->isoctl(iso, RECV_SET_CHANNEL_MASK,
					 (unsigned long)&mask);
}
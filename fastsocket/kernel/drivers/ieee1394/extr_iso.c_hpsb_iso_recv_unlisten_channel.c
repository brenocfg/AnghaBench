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
struct hpsb_iso {scalar_t__ type; int channel; TYPE_2__* host; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int (* isoctl ) (struct hpsb_iso*,int /*<<< orphan*/ ,unsigned char) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HPSB_ISO_RECV ; 
 int /*<<< orphan*/  RECV_UNLISTEN_CHANNEL ; 
 int stub1 (struct hpsb_iso*,int /*<<< orphan*/ ,unsigned char) ; 

int hpsb_iso_recv_unlisten_channel(struct hpsb_iso *iso, unsigned char channel)
{
	if (iso->type != HPSB_ISO_RECV || iso->channel != -1 || channel >= 64)
		return -EINVAL;
	return iso->host->driver->isoctl(iso, RECV_UNLISTEN_CHANNEL, channel);
}
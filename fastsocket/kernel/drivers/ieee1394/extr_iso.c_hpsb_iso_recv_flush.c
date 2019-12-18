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
struct hpsb_iso {scalar_t__ type; TYPE_2__* host; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int (* isoctl ) (struct hpsb_iso*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HPSB_ISO_RECV ; 
 int /*<<< orphan*/  RECV_FLUSH ; 
 int stub1 (struct hpsb_iso*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hpsb_iso_recv_flush(struct hpsb_iso *iso)
{
	if (iso->type != HPSB_ISO_RECV)
		return -EINVAL;
	return iso->host->driver->isoctl(iso, RECV_FLUSH, 0);
}
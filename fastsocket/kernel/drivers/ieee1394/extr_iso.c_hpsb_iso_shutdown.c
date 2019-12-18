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
struct hpsb_iso {int flags; scalar_t__ type; int /*<<< orphan*/  data_buf; TYPE_2__* host; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* isoctl ) (struct hpsb_iso*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int HPSB_ISO_DRIVER_INIT ; 
 scalar_t__ HPSB_ISO_XMIT ; 
 int /*<<< orphan*/  RECV_SHUTDOWN ; 
 int /*<<< orphan*/  XMIT_SHUTDOWN ; 
 int /*<<< orphan*/  dma_region_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpsb_iso_stop (struct hpsb_iso*) ; 
 int /*<<< orphan*/  kfree (struct hpsb_iso*) ; 
 int /*<<< orphan*/  stub1 (struct hpsb_iso*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hpsb_iso_shutdown(struct hpsb_iso *iso)
{
	if (iso->flags & HPSB_ISO_DRIVER_INIT) {
		hpsb_iso_stop(iso);
		iso->host->driver->isoctl(iso, iso->type == HPSB_ISO_XMIT ?
					  XMIT_SHUTDOWN : RECV_SHUTDOWN, 0);
		iso->flags &= ~HPSB_ISO_DRIVER_INIT;
	}

	dma_region_free(&iso->data_buf);
	kfree(iso);
}
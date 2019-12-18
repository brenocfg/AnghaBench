#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hpsb_iso {int speed; int /*<<< orphan*/  flags; } ;
struct hpsb_host {TYPE_1__* driver; } ;
struct TYPE_2__ {scalar_t__ (* isoctl ) (struct hpsb_iso*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HPSB_ISO_DMA_DEFAULT ; 
 int /*<<< orphan*/  HPSB_ISO_DRIVER_INIT ; 
 int /*<<< orphan*/  HPSB_ISO_XMIT ; 
 int /*<<< orphan*/  XMIT_INIT ; 
 struct hpsb_iso* hpsb_iso_common_init (struct hpsb_host*,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int /*<<< orphan*/ ,int,void (*) (struct hpsb_iso*)) ; 
 int /*<<< orphan*/  hpsb_iso_shutdown (struct hpsb_iso*) ; 
 scalar_t__ stub1 (struct hpsb_iso*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct hpsb_iso *hpsb_iso_xmit_init(struct hpsb_host *host,
				    unsigned int data_buf_size,
				    unsigned int buf_packets,
				    int channel,
				    int speed,
				    int irq_interval,
				    void (*callback) (struct hpsb_iso *))
{
	struct hpsb_iso *iso = hpsb_iso_common_init(host, HPSB_ISO_XMIT,
						    data_buf_size, buf_packets,
						    channel,
						    HPSB_ISO_DMA_DEFAULT,
						    irq_interval, callback);
	if (!iso)
		return NULL;

	iso->speed = speed;

	/* tell the driver to start working */
	if (host->driver->isoctl(iso, XMIT_INIT, 0))
		goto err;

	iso->flags |= HPSB_ISO_DRIVER_INIT;
	return iso;

      err:
	hpsb_iso_shutdown(iso);
	return NULL;
}
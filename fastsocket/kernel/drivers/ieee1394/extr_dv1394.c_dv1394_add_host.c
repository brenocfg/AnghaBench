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
struct ti_ohci {int dummy; } ;
struct hpsb_host {int id; scalar_t__ hostdata; TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DV1394_NTSC ; 
 int /*<<< orphan*/  DV1394_PAL ; 
 int /*<<< orphan*/  IEEE1394_MAJOR ; 
 int IEEE1394_MINOR_BLOCK_DV1394 ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MODE_RECEIVE ; 
 int /*<<< orphan*/  MODE_TRANSMIT ; 
 int /*<<< orphan*/  OHCI1394_DRIVER_NAME ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dv1394_init (struct ti_ohci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsb_protocol_class ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dv1394_add_host(struct hpsb_host *host)
{
	struct ti_ohci *ohci;
	int id = host->id;

	/* We only work with the OHCI-1394 driver */
	if (strcmp(host->driver->name, OHCI1394_DRIVER_NAME))
		return;

	ohci = (struct ti_ohci *)host->hostdata;

	device_create(hpsb_protocol_class, NULL,
		      MKDEV(IEEE1394_MAJOR,
			    IEEE1394_MINOR_BLOCK_DV1394 * 16 + (id<<2)),
		      NULL, "dv1394-%d", id);

	dv1394_init(ohci, DV1394_NTSC, MODE_RECEIVE);
	dv1394_init(ohci, DV1394_NTSC, MODE_TRANSMIT);
	dv1394_init(ohci, DV1394_PAL, MODE_RECEIVE);
	dv1394_init(ohci, DV1394_PAL, MODE_TRANSMIT);
}
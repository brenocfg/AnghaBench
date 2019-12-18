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
struct hpsb_iso {int /*<<< orphan*/  flags; TYPE_2__* host; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int (* isoctl ) (struct hpsb_iso*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HPSB_ISO_DRIVER_STARTED ; 
 int /*<<< orphan*/  XMIT_START ; 
 int stub1 (struct hpsb_iso*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_iso_xmit_start(struct hpsb_iso *iso, int cycle)
{
	int retval = iso->host->driver->isoctl(iso, XMIT_START, cycle);
	if (retval)
		return retval;

	iso->flags |= HPSB_ISO_DRIVER_STARTED;
	return retval;
}
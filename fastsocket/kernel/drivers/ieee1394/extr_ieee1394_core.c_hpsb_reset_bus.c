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
struct hpsb_host {TYPE_1__* driver; int /*<<< orphan*/  in_bus_reset; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* devctl ) (struct hpsb_host*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RESET_BUS ; 
 int /*<<< orphan*/  stub1 (struct hpsb_host*,int /*<<< orphan*/ ,int) ; 

int hpsb_reset_bus(struct hpsb_host *host, int type)
{
	if (!host->in_bus_reset) {
		host->driver->devctl(host, RESET_BUS, type);
		return 0;
	} else {
		return 1;
	}
}
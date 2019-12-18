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
typedef  int /*<<< orphan*/  ushort ;
struct ipath_devdata {TYPE_1__* ipath_kregs; void* ipath_p0_rcvegrcnt; void* ipath_portcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_rcvegrcnt; int /*<<< orphan*/  kr_portcnt; } ;

/* Variables and functions */
 void* ipath_read_kreg32 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipath_ht_config_ports(struct ipath_devdata *dd, ushort cfgports)
{
	dd->ipath_portcnt =
		ipath_read_kreg32(dd, dd->ipath_kregs->kr_portcnt);
	dd->ipath_p0_rcvegrcnt =
		ipath_read_kreg32(dd, dd->ipath_kregs->kr_rcvegrcnt);
}
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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct qib_devdata {TYPE_1__* cspec; int /*<<< orphan*/  pport; } ;
struct TYPE_2__ {scalar_t__ lastlinkrecov; } ;

/* Variables and functions */
 scalar_t__ IB_PORT_ACTIVE ; 
 int /*<<< orphan*/  QIB_IB_LINKDOWN ; 
 int /*<<< orphan*/  cr_iblinkerrrecov ; 
 scalar_t__ qib_6120_iblink_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_set_linkstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read_6120_creg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chk_6120_linkrecovery(struct qib_devdata *dd, u64 ibcs)
{
	int ret = 1;
	u32 ibstate = qib_6120_iblink_state(ibcs);
	u32 linkrecov = read_6120_creg32(dd, cr_iblinkerrrecov);

	if (linkrecov != dd->cspec->lastlinkrecov) {
		/* and no more until active again */
		dd->cspec->lastlinkrecov = 0;
		qib_set_linkstate(dd->pport, QIB_IB_LINKDOWN);
		ret = 0;
	}
	if (ibstate == IB_PORT_ACTIVE)
		dd->cspec->lastlinkrecov =
			read_6120_creg32(dd, cr_iblinkerrrecov);
	return ret;
}
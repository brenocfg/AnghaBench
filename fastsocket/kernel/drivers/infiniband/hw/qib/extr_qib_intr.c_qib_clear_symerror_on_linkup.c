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
struct TYPE_3__ {int /*<<< orphan*/  z_symbol_error_counter; } ;
struct qib_pportdata {int lflags; TYPE_2__* dd; TYPE_1__ ibport_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* f_portcntr ) (struct qib_pportdata*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int QIBL_LINKACTIVE ; 
 int /*<<< orphan*/  QIBPORTCNTR_IBSYMBOLERR ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 

void qib_clear_symerror_on_linkup(unsigned long opaque)
{
	struct qib_pportdata *ppd = (struct qib_pportdata *)opaque;

	if (ppd->lflags & QIBL_LINKACTIVE)
		return;

	ppd->ibport_data.z_symbol_error_counter =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_IBSYMBOLERR);
}
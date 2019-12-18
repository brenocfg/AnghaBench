#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xiocb_fwinfo {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  fwi_reserved3; int /*<<< orphan*/  fwi_reserved2; int /*<<< orphan*/  fwi_reserved1; int /*<<< orphan*/  fwi_bootarea_size; int /*<<< orphan*/  fwi_bootarea_pa; int /*<<< orphan*/  fwi_bootarea_va; int /*<<< orphan*/  fwi_boardid; int /*<<< orphan*/  fwi_flags; int /*<<< orphan*/  fwi_totalmem; int /*<<< orphan*/  fwi_version; } ;
struct TYPE_6__ {TYPE_1__ xiocb_fwinfo; } ;
struct cfe_xiocb {scalar_t__ xiocb_status; int xiocb_psize; TYPE_2__ plist; scalar_t__ xiocb_flags; scalar_t__ xiocb_handle; int /*<<< orphan*/  xiocb_fcode; } ;
struct TYPE_7__ {int /*<<< orphan*/  fwi_reserved3; int /*<<< orphan*/  fwi_reserved2; int /*<<< orphan*/  fwi_reserved1; int /*<<< orphan*/  fwi_bootarea_size; int /*<<< orphan*/  fwi_bootarea_pa; int /*<<< orphan*/  fwi_bootarea_va; int /*<<< orphan*/  fwi_boardid; int /*<<< orphan*/  fwi_flags; int /*<<< orphan*/  fwi_totalmem; int /*<<< orphan*/  fwi_version; } ;
typedef  TYPE_3__ cfe_fwinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFE_CMD_FW_GETINFO ; 
 int /*<<< orphan*/  cfe_iocb_dispatch (struct cfe_xiocb*) ; 

int cfe_getfwinfo(cfe_fwinfo_t * info)
{
	struct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_GETINFO;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = sizeof(struct xiocb_fwinfo);

	cfe_iocb_dispatch(&xiocb);

	if (xiocb.xiocb_status < 0)
		return xiocb.xiocb_status;

	info->fwi_version = xiocb.plist.xiocb_fwinfo.fwi_version;
	info->fwi_totalmem = xiocb.plist.xiocb_fwinfo.fwi_totalmem;
	info->fwi_flags = xiocb.plist.xiocb_fwinfo.fwi_flags;
	info->fwi_boardid = xiocb.plist.xiocb_fwinfo.fwi_boardid;
	info->fwi_bootarea_va = xiocb.plist.xiocb_fwinfo.fwi_bootarea_va;
	info->fwi_bootarea_pa = xiocb.plist.xiocb_fwinfo.fwi_bootarea_pa;
	info->fwi_bootarea_size =
	    xiocb.plist.xiocb_fwinfo.fwi_bootarea_size;
#if 0
	info->fwi_reserved1 = xiocb.plist.xiocb_fwinfo.fwi_reserved1;
	info->fwi_reserved2 = xiocb.plist.xiocb_fwinfo.fwi_reserved2;
	info->fwi_reserved3 = xiocb.plist.xiocb_fwinfo.fwi_reserved3;
#endif

	return 0;
}
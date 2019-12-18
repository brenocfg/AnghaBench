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
typedef  int /*<<< orphan*/  u64 ;
struct xiocb_meminfo {int dummy; } ;
struct TYPE_3__ {int mi_idx; int /*<<< orphan*/  mi_type; int /*<<< orphan*/  mi_size; int /*<<< orphan*/  mi_addr; } ;
struct TYPE_4__ {TYPE_1__ xiocb_meminfo; } ;
struct cfe_xiocb {scalar_t__ xiocb_status; int xiocb_flags; int xiocb_psize; TYPE_2__ plist; scalar_t__ xiocb_handle; int /*<<< orphan*/  xiocb_fcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFE_CMD_FW_MEMENUM ; 
 int /*<<< orphan*/  cfe_iocb_dispatch (struct cfe_xiocb*) ; 

int
cfe_enummem(int idx, int flags, u64 *start, u64 *length, u64 *type)
{
	struct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_MEMENUM;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = flags;
	xiocb.xiocb_psize = sizeof(struct xiocb_meminfo);
	xiocb.plist.xiocb_meminfo.mi_idx = idx;

	cfe_iocb_dispatch(&xiocb);

	if (xiocb.xiocb_status < 0)
		return xiocb.xiocb_status;

	*start = xiocb.plist.xiocb_meminfo.mi_addr;
	*length = xiocb.plist.xiocb_meminfo.mi_size;
	*type = xiocb.plist.xiocb_meminfo.mi_type;

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cfe_xiocb {int xiocb_status; int xiocb_handle; scalar_t__ xiocb_psize; scalar_t__ xiocb_flags; int /*<<< orphan*/  xiocb_fcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFE_CMD_DEV_CLOSE ; 
 int /*<<< orphan*/  cfe_iocb_dispatch (struct cfe_xiocb*) ; 

int cfe_close(int handle)
{
	struct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_CLOSE;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = handle;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = 0;

	cfe_iocb_dispatch(&xiocb);

	return xiocb.xiocb_status;

}
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
struct xiocb_buffer {int dummy; } ;
struct TYPE_3__ {int buf_length; int buf_retlen; int /*<<< orphan*/  buf_ptr; int /*<<< orphan*/  buf_offset; } ;
struct TYPE_4__ {TYPE_1__ xiocb_buffer; } ;
struct cfe_xiocb {scalar_t__ xiocb_status; int xiocb_handle; int xiocb_psize; TYPE_2__ plist; scalar_t__ xiocb_flags; int /*<<< orphan*/  xiocb_fcode; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  CFE_CMD_DEV_READ ; 
 int /*<<< orphan*/  XPTR_FROM_NATIVE (unsigned char*) ; 
 int /*<<< orphan*/  cfe_iocb_dispatch (struct cfe_xiocb*) ; 

int cfe_readblk(int handle, s64 offset, unsigned char *buffer, int length)
{
	struct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_READ;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = handle;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = sizeof(struct xiocb_buffer);
	xiocb.plist.xiocb_buffer.buf_offset = offset;
	xiocb.plist.xiocb_buffer.buf_ptr = XPTR_FROM_NATIVE(buffer);
	xiocb.plist.xiocb_buffer.buf_length = length;

	cfe_iocb_dispatch(&xiocb);

	if (xiocb.xiocb_status < 0)
		return xiocb.xiocb_status;
	return xiocb.plist.xiocb_buffer.buf_retlen;
}
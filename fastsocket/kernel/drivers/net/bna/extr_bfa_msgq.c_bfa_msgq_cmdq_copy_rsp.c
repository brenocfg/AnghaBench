#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int /*<<< orphan*/  i2htok; } ;
struct TYPE_9__ {TYPE_2__ mtag; } ;
struct bfi_msgq_h2i_cmdq_copy_rsp {int /*<<< orphan*/  data; TYPE_4__ mh; } ;
struct TYPE_10__ {int /*<<< orphan*/ * msg; } ;
struct TYPE_6__ {scalar_t__ kva; } ;
struct bfa_msgq_cmdq {int bytes_to_copy; TYPE_5__ copy_mb; TYPE_3__* msgq; scalar_t__ offset; int /*<<< orphan*/  token; TYPE_1__ addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 int BFI_CMD_COPY_SZ ; 
 int /*<<< orphan*/  BFI_MC_MSGQ ; 
 int /*<<< orphan*/  BFI_MSGQ_H2I_CMDQ_COPY_RSP ; 
 int /*<<< orphan*/  bfa_msgq_cmdq_copy_next (struct bfa_msgq_cmdq*) ; 
 int /*<<< orphan*/  bfa_nw_ioc_mbox_queue (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/  (*) (struct bfa_msgq_cmdq*),struct bfa_msgq_cmdq*) ; 
 int /*<<< orphan*/  bfi_h2i_set (TYPE_4__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct bfi_msgq_h2i_cmdq_copy_rsp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_msgq_cmdq_copy_rsp(struct bfa_msgq_cmdq *cmdq)
{
	struct bfi_msgq_h2i_cmdq_copy_rsp *rsp =
		(struct bfi_msgq_h2i_cmdq_copy_rsp *)&cmdq->copy_mb.msg[0];
	int copied;
	u8 *addr = (u8 *)cmdq->addr.kva;

	memset(rsp, 0, sizeof(struct bfi_msgq_h2i_cmdq_copy_rsp));
	bfi_h2i_set(rsp->mh, BFI_MC_MSGQ, BFI_MSGQ_H2I_CMDQ_COPY_RSP, 0);
	rsp->mh.mtag.i2htok = htons(cmdq->token);
	copied = (cmdq->bytes_to_copy >= BFI_CMD_COPY_SZ) ? BFI_CMD_COPY_SZ :
		cmdq->bytes_to_copy;
	addr += cmdq->offset;
	memcpy(rsp->data, addr, copied);

	cmdq->token++;
	cmdq->offset += copied;
	cmdq->bytes_to_copy -= copied;

	if (!bfa_nw_ioc_mbox_queue(cmdq->msgq->ioc, &cmdq->copy_mb,
				bfa_msgq_cmdq_copy_next, cmdq)) {
		bfa_msgq_cmdq_copy_next(cmdq);
	}
}
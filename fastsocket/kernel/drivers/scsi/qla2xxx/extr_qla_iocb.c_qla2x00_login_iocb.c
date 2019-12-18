#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_11__ {int flags; } ;
struct TYPE_12__ {TYPE_2__ logio; } ;
struct srb_iocb {TYPE_3__ u; } ;
struct qla_hw_data {int dummy; } ;
struct mbx_entry {void* mb9; void* mb3; void* mb2; void* mb1; void* mb10; void* mb0; int /*<<< orphan*/  loop_id; int /*<<< orphan*/  entry_type; } ;
struct TYPE_10__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_17__ {TYPE_7__* fcport; TYPE_1__ u; } ;
typedef  TYPE_8__ srb_t ;
struct TYPE_13__ {int domain; int area; int al_pa; } ;
struct TYPE_14__ {TYPE_4__ b; } ;
struct TYPE_16__ {int loop_id; TYPE_6__* vha; TYPE_5__ d_id; } ;
struct TYPE_15__ {int vp_idx; struct qla_hw_data* hw; } ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_1 ; 
 scalar_t__ HAS_EXTENDED_IDS (struct qla_hw_data*) ; 
 int MBC_LOGIN_FABRIC_PORT ; 
 int /*<<< orphan*/  MBX_IOCB_TYPE ; 
 int /*<<< orphan*/  SET_TARGET_ID (struct qla_hw_data*,int /*<<< orphan*/ ,int) ; 
 int SRB_LOGIN_COND_PLOGI ; 
 int SRB_LOGIN_SKIP_PRLI ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static void
qla2x00_login_iocb(srb_t *sp, struct mbx_entry *mbx)
{
	struct qla_hw_data *ha = sp->fcport->vha->hw;
	struct srb_iocb *lio = &sp->u.iocb_cmd;
	uint16_t opts;

	mbx->entry_type = MBX_IOCB_TYPE;
	SET_TARGET_ID(ha, mbx->loop_id, sp->fcport->loop_id);
	mbx->mb0 = cpu_to_le16(MBC_LOGIN_FABRIC_PORT);
	opts = lio->u.logio.flags & SRB_LOGIN_COND_PLOGI ? BIT_0 : 0;
	opts |= lio->u.logio.flags & SRB_LOGIN_SKIP_PRLI ? BIT_1 : 0;
	if (HAS_EXTENDED_IDS(ha)) {
		mbx->mb1 = cpu_to_le16(sp->fcport->loop_id);
		mbx->mb10 = cpu_to_le16(opts);
	} else {
		mbx->mb1 = cpu_to_le16((sp->fcport->loop_id << 8) | opts);
	}
	mbx->mb2 = cpu_to_le16(sp->fcport->d_id.b.domain);
	mbx->mb3 = cpu_to_le16(sp->fcport->d_id.b.area << 8 |
	    sp->fcport->d_id.b.al_pa);
	mbx->mb9 = cpu_to_le16(sp->fcport->vha->vp_idx);
}
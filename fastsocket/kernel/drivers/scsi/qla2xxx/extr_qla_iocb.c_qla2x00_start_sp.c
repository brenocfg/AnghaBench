#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {int /*<<< orphan*/  hardware_lock; int /*<<< orphan*/ * req_q_map; } ;
struct TYPE_22__ {int type; TYPE_1__* fcport; } ;
typedef  TYPE_2__ srb_t ;
struct TYPE_23__ {struct qla_hw_data* hw; } ;
struct TYPE_21__ {TYPE_7__* vha; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLAFX00 (struct qla_hw_data*) ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
#define  SRB_ABT_CMD 137 
#define  SRB_ADISC_CMD 136 
#define  SRB_CT_CMD 135 
#define  SRB_ELS_CMD_HST 134 
#define  SRB_ELS_CMD_RPT 133 
#define  SRB_FXIOCB_BCMD 132 
#define  SRB_FXIOCB_DCMD 131 
#define  SRB_LOGIN_CMD 130 
#define  SRB_LOGOUT_CMD 129 
#define  SRB_TM_CMD 128 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_7__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla24xx_adisc_iocb (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  qla24xx_ct_iocb (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  qla24xx_els_iocb (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  qla24xx_login_iocb (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  qla24xx_logout_iocb (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  qla24xx_tm_iocb (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  qla2x00_adisc_iocb (TYPE_2__*,void*) ; 
 void* qla2x00_alloc_iocbs (TYPE_7__*,TYPE_2__*) ; 
 int /*<<< orphan*/  qla2x00_ct_iocb (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  qla2x00_login_iocb (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  qla2x00_logout_iocb (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  qla2x00_start_iocbs (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlafx00_abort_iocb (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  qlafx00_fxdisc_iocb (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  qlafx00_tm_iocb (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

int
qla2x00_start_sp(srb_t *sp)
{
	int rval;
	struct qla_hw_data *ha = sp->fcport->vha->hw;
	void *pkt;
	unsigned long flags;

	rval = QLA_FUNCTION_FAILED;
	spin_lock_irqsave(&ha->hardware_lock, flags);
	pkt = qla2x00_alloc_iocbs(sp->fcport->vha, sp);
	if (!pkt) {
		ql_log(ql_log_warn, sp->fcport->vha, 0x700c,
		    "qla2x00_alloc_iocbs failed.\n");
		goto done;
	}

	rval = QLA_SUCCESS;
	switch (sp->type) {
	case SRB_LOGIN_CMD:
		IS_FWI2_CAPABLE(ha) ?
		    qla24xx_login_iocb(sp, pkt):
		    qla2x00_login_iocb(sp, pkt);
		break;
	case SRB_LOGOUT_CMD:
		IS_FWI2_CAPABLE(ha) ?
		    qla24xx_logout_iocb(sp, pkt):
		    qla2x00_logout_iocb(sp, pkt);
		break;
	case SRB_ELS_CMD_RPT:
	case SRB_ELS_CMD_HST:
		qla24xx_els_iocb(sp, pkt);
		break;
	case SRB_CT_CMD:
		IS_FWI2_CAPABLE(ha) ?
		    qla24xx_ct_iocb(sp, pkt) :
		    qla2x00_ct_iocb(sp, pkt);
		break;
	case SRB_ADISC_CMD:
		IS_FWI2_CAPABLE(ha) ?
		    qla24xx_adisc_iocb(sp, pkt):
		    qla2x00_adisc_iocb(sp, pkt);
		break;
	case SRB_TM_CMD:
		IS_QLAFX00(ha) ?
		    qlafx00_tm_iocb(sp, pkt) :
		    qla24xx_tm_iocb(sp, pkt);
		break;
	case SRB_FXIOCB_DCMD:
	case SRB_FXIOCB_BCMD:
		qlafx00_fxdisc_iocb(sp, pkt);
		break;
	case SRB_ABT_CMD:
		qlafx00_abort_iocb(sp, pkt);
		break;
	default:
		break;
	}

	wmb();
	qla2x00_start_iocbs(sp->fcport->vha, ha->req_q_map[0]);
done:
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	return rval;
}
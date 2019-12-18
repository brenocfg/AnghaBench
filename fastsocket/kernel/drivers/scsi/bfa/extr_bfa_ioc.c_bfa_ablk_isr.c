#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ msg_class; int /*<<< orphan*/  msg_id; } ;
struct bfi_mbmsg_s {TYPE_1__ mh; } ;
struct bfi_ablk_i2h_rsp_s {int /*<<< orphan*/  status; int /*<<< orphan*/  pcifn; int /*<<< orphan*/  port_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  kva; } ;
struct bfa_ablk_s {int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  busy; int /*<<< orphan*/ * pcifn; TYPE_3__* ioc; int /*<<< orphan*/ * cfg; TYPE_2__ dma_addr; } ;
struct bfa_ablk_cfg_s {int dummy; } ;
typedef  int /*<<< orphan*/  (* bfa_ablk_cbfn_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_6__ {int /*<<< orphan*/  port_mode_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
#define  BFI_ABLK_I2H_ADPT_CONFIG 135 
#define  BFI_ABLK_I2H_OPTROM_DISABLE 134 
#define  BFI_ABLK_I2H_OPTROM_ENABLE 133 
#define  BFI_ABLK_I2H_PF_CREATE 132 
#define  BFI_ABLK_I2H_PF_DELETE 131 
#define  BFI_ABLK_I2H_PF_UPDATE 130 
#define  BFI_ABLK_I2H_PORT_CONFIG 129 
#define  BFI_ABLK_I2H_QUERY 128 
 scalar_t__ BFI_MC_ABLK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_ablk_config_swap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_ablk_isr(void *cbarg, struct bfi_mbmsg_s *msg)
{
	struct bfa_ablk_s *ablk = (struct bfa_ablk_s *)cbarg;
	struct bfi_ablk_i2h_rsp_s *rsp = (struct bfi_ablk_i2h_rsp_s *)msg;
	bfa_ablk_cbfn_t cbfn;

	WARN_ON(msg->mh.msg_class != BFI_MC_ABLK);
	bfa_trc(ablk->ioc, msg->mh.msg_id);

	switch (msg->mh.msg_id) {
	case BFI_ABLK_I2H_QUERY:
		if (rsp->status == BFA_STATUS_OK) {
			memcpy(ablk->cfg, ablk->dma_addr.kva,
				sizeof(struct bfa_ablk_cfg_s));
			bfa_ablk_config_swap(ablk->cfg);
			ablk->cfg = NULL;
		}
		break;

	case BFI_ABLK_I2H_ADPT_CONFIG:
	case BFI_ABLK_I2H_PORT_CONFIG:
		/* update config port mode */
		ablk->ioc->port_mode_cfg = rsp->port_mode;

	case BFI_ABLK_I2H_PF_DELETE:
	case BFI_ABLK_I2H_PF_UPDATE:
	case BFI_ABLK_I2H_OPTROM_ENABLE:
	case BFI_ABLK_I2H_OPTROM_DISABLE:
		/* No-op */
		break;

	case BFI_ABLK_I2H_PF_CREATE:
		*(ablk->pcifn) = rsp->pcifn;
		ablk->pcifn = NULL;
		break;

	default:
		WARN_ON(1);
	}

	ablk->busy = BFA_FALSE;
	if (ablk->cbfn) {
		cbfn = ablk->cbfn;
		ablk->cbfn = NULL;
		cbfn(ablk->cbarg, rsp->status);
	}
}
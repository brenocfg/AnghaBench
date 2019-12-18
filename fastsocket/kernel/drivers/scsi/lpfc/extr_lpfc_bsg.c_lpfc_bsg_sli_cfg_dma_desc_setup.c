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
typedef  size_t uint32_t ;
struct TYPE_8__ {TYPE_5__* hbd; } ;
struct TYPE_7__ {TYPE_1__* mse; } ;
struct TYPE_9__ {TYPE_3__ sli_config_emb1_subsys; TYPE_2__ sli_config_emb0_subsys; } ;
struct lpfc_sli_config_mbox {TYPE_4__ un; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {scalar_t__ phys; scalar_t__ virt; } ;
typedef  enum nemb_type { ____Placeholder_nemb_type } nemb_type ;
struct TYPE_10__ {void* pa_lo; void* pa_hi; } ;
struct TYPE_6__ {void* pa_lo; void* pa_hi; int /*<<< orphan*/  buf_len; } ;
typedef  int /*<<< orphan*/  MAILBOX_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_LIBDFC ; 
 int /*<<< orphan*/  bsg_bf_get (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  lpfc_mbox_sli_config_ecmn_hbd_len ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,void*,void*) ; 
 int nemb_mse ; 
 void* putPaddrHigh (scalar_t__) ; 
 void* putPaddrLow (scalar_t__) ; 

__attribute__((used)) static void
lpfc_bsg_sli_cfg_dma_desc_setup(struct lpfc_hba *phba, enum nemb_type nemb_tp,
				uint32_t index, struct lpfc_dmabuf *mbx_dmabuf,
				struct lpfc_dmabuf *ext_dmabuf)
{
	struct lpfc_sli_config_mbox *sli_cfg_mbx;

	/* pointer to the start of mailbox command */
	sli_cfg_mbx = (struct lpfc_sli_config_mbox *)mbx_dmabuf->virt;

	if (nemb_tp == nemb_mse) {
		if (index == 0) {
			sli_cfg_mbx->un.sli_config_emb0_subsys.
				mse[index].pa_hi =
				putPaddrHigh(mbx_dmabuf->phys +
					     sizeof(MAILBOX_t));
			sli_cfg_mbx->un.sli_config_emb0_subsys.
				mse[index].pa_lo =
				putPaddrLow(mbx_dmabuf->phys +
					    sizeof(MAILBOX_t));
			lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
					"2943 SLI_CONFIG(mse)[%d], "
					"bufLen:%d, addrHi:x%x, addrLo:x%x\n",
					index,
					sli_cfg_mbx->un.sli_config_emb0_subsys.
					mse[index].buf_len,
					sli_cfg_mbx->un.sli_config_emb0_subsys.
					mse[index].pa_hi,
					sli_cfg_mbx->un.sli_config_emb0_subsys.
					mse[index].pa_lo);
		} else {
			sli_cfg_mbx->un.sli_config_emb0_subsys.
				mse[index].pa_hi =
				putPaddrHigh(ext_dmabuf->phys);
			sli_cfg_mbx->un.sli_config_emb0_subsys.
				mse[index].pa_lo =
				putPaddrLow(ext_dmabuf->phys);
			lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
					"2944 SLI_CONFIG(mse)[%d], "
					"bufLen:%d, addrHi:x%x, addrLo:x%x\n",
					index,
					sli_cfg_mbx->un.sli_config_emb0_subsys.
					mse[index].buf_len,
					sli_cfg_mbx->un.sli_config_emb0_subsys.
					mse[index].pa_hi,
					sli_cfg_mbx->un.sli_config_emb0_subsys.
					mse[index].pa_lo);
		}
	} else {
		if (index == 0) {
			sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_hi =
				putPaddrHigh(mbx_dmabuf->phys +
					     sizeof(MAILBOX_t));
			sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_lo =
				putPaddrLow(mbx_dmabuf->phys +
					    sizeof(MAILBOX_t));
			lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
					"3007 SLI_CONFIG(hbd)[%d], "
					"bufLen:%d, addrHi:x%x, addrLo:x%x\n",
				index,
				bsg_bf_get(lpfc_mbox_sli_config_ecmn_hbd_len,
				&sli_cfg_mbx->un.
				sli_config_emb1_subsys.hbd[index]),
				sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_hi,
				sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_lo);

		} else {
			sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_hi =
				putPaddrHigh(ext_dmabuf->phys);
			sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_lo =
				putPaddrLow(ext_dmabuf->phys);
			lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
					"3008 SLI_CONFIG(hbd)[%d], "
					"bufLen:%d, addrHi:x%x, addrLo:x%x\n",
				index,
				bsg_bf_get(lpfc_mbox_sli_config_ecmn_hbd_len,
				&sli_cfg_mbx->un.
				sli_config_emb1_subsys.hbd[index]),
				sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_hi,
				sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_lo);
		}
	}
	return;
}
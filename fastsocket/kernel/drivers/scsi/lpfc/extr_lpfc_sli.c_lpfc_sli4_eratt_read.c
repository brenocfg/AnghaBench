#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct lpfc_register {int word0; } ;
struct TYPE_6__ {int /*<<< orphan*/  ERR2regaddr; int /*<<< orphan*/  ERR1regaddr; int /*<<< orphan*/  STATUSregaddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  UERRHIregaddr; int /*<<< orphan*/  UERRLOregaddr; } ;
struct TYPE_7__ {TYPE_2__ if_type2; TYPE_1__ if_type0; } ;
struct TYPE_8__ {int ue_mask_lo; int ue_mask_hi; TYPE_3__ u; int /*<<< orphan*/  PSMPHRregaddr; struct lpfc_register sli_intf; } ;
struct lpfc_hba {int* work_status; int /*<<< orphan*/  hba_flag; int /*<<< orphan*/  work_ha; TYPE_4__ sli4_hba; int /*<<< orphan*/  work_hs; } ;

/* Variables and functions */
 int /*<<< orphan*/  HA_ERATT ; 
 int /*<<< orphan*/  HBA_ERATT_HANDLED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
#define  LPFC_SLI_INTF_IF_TYPE_0 130 
#define  LPFC_SLI_INTF_IF_TYPE_1 129 
#define  LPFC_SLI_INTF_IF_TYPE_2 128 
 int /*<<< orphan*/  UNPLUG_ERR ; 
 int bf_get (int /*<<< orphan*/ ,struct lpfc_register*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  lpfc_readl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lpfc_sli_intf_if_type ; 
 int /*<<< orphan*/  lpfc_sliport_status_err ; 
 void* readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_sli4_eratt_read(struct lpfc_hba *phba)
{
	uint32_t uerr_sta_hi, uerr_sta_lo;
	uint32_t if_type, portsmphr;
	struct lpfc_register portstat_reg;

	/*
	 * For now, use the SLI4 device internal unrecoverable error
	 * registers for error attention. This can be changed later.
	 */
	if_type = bf_get(lpfc_sli_intf_if_type, &phba->sli4_hba.sli_intf);
	switch (if_type) {
	case LPFC_SLI_INTF_IF_TYPE_0:
		if (lpfc_readl(phba->sli4_hba.u.if_type0.UERRLOregaddr,
			&uerr_sta_lo) ||
			lpfc_readl(phba->sli4_hba.u.if_type0.UERRHIregaddr,
			&uerr_sta_hi)) {
			phba->work_hs |= UNPLUG_ERR;
			phba->work_ha |= HA_ERATT;
			phba->hba_flag |= HBA_ERATT_HANDLED;
			return 1;
		}
		if ((~phba->sli4_hba.ue_mask_lo & uerr_sta_lo) ||
		    (~phba->sli4_hba.ue_mask_hi & uerr_sta_hi)) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"1423 HBA Unrecoverable error: "
					"uerr_lo_reg=0x%x, uerr_hi_reg=0x%x, "
					"ue_mask_lo_reg=0x%x, "
					"ue_mask_hi_reg=0x%x\n",
					uerr_sta_lo, uerr_sta_hi,
					phba->sli4_hba.ue_mask_lo,
					phba->sli4_hba.ue_mask_hi);
			phba->work_status[0] = uerr_sta_lo;
			phba->work_status[1] = uerr_sta_hi;
			phba->work_ha |= HA_ERATT;
			phba->hba_flag |= HBA_ERATT_HANDLED;
			return 1;
		}
		break;
	case LPFC_SLI_INTF_IF_TYPE_2:
		if (lpfc_readl(phba->sli4_hba.u.if_type2.STATUSregaddr,
			&portstat_reg.word0) ||
			lpfc_readl(phba->sli4_hba.PSMPHRregaddr,
			&portsmphr)){
			phba->work_hs |= UNPLUG_ERR;
			phba->work_ha |= HA_ERATT;
			phba->hba_flag |= HBA_ERATT_HANDLED;
			return 1;
		}
		if (bf_get(lpfc_sliport_status_err, &portstat_reg)) {
			phba->work_status[0] =
				readl(phba->sli4_hba.u.if_type2.ERR1regaddr);
			phba->work_status[1] =
				readl(phba->sli4_hba.u.if_type2.ERR2regaddr);
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"2885 Port Status Event: "
					"port status reg 0x%x, "
					"port smphr reg 0x%x, "
					"error 1=0x%x, error 2=0x%x\n",
					portstat_reg.word0,
					portsmphr,
					phba->work_status[0],
					phba->work_status[1]);
			phba->work_ha |= HA_ERATT;
			phba->hba_flag |= HBA_ERATT_HANDLED;
			return 1;
		}
		break;
	case LPFC_SLI_INTF_IF_TYPE_1:
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"2886 HBA Error Attention on unsupported "
				"if type %d.", if_type);
		return 1;
	}

	return 0;
}
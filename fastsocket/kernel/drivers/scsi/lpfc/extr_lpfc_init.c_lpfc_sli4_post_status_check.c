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
struct TYPE_5__ {int /*<<< orphan*/  UERRHIregaddr; int /*<<< orphan*/  UERRLOregaddr; int /*<<< orphan*/  UEMASKHIregaddr; int /*<<< orphan*/  UEMASKLOregaddr; } ;
struct TYPE_7__ {TYPE_2__ if_type2; TYPE_1__ if_type0; } ;
struct TYPE_8__ {int ue_mask_lo; int ue_mask_hi; TYPE_3__ u; struct lpfc_register sli_intf; int /*<<< orphan*/  PSMPHRregaddr; } ;
struct lpfc_hba {int* work_status; TYPE_4__ sli4_hba; } ;
typedef  int /*<<< orphan*/  reg_data ;
typedef  int /*<<< orphan*/  portsmphr_reg ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_INIT ; 
 scalar_t__ LPFC_POST_STAGE_PORT_READY ; 
#define  LPFC_SLI_INTF_IF_TYPE_0 130 
#define  LPFC_SLI_INTF_IF_TYPE_1 129 
#define  LPFC_SLI_INTF_IF_TYPE_2 128 
 scalar_t__ bf_get (int /*<<< orphan*/ ,struct lpfc_register*) ; 
 int /*<<< orphan*/  lpfc_port_smphr_host_scratch ; 
 int /*<<< orphan*/  lpfc_port_smphr_ipc ; 
 int /*<<< orphan*/  lpfc_port_smphr_nip ; 
 int /*<<< orphan*/  lpfc_port_smphr_perr ; 
 int /*<<< orphan*/  lpfc_port_smphr_port_status ; 
 int /*<<< orphan*/  lpfc_port_smphr_scr1 ; 
 int /*<<< orphan*/  lpfc_port_smphr_scr2 ; 
 int /*<<< orphan*/  lpfc_port_smphr_sfi ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int,...) ; 
 scalar_t__ lpfc_readl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lpfc_sli_intf_func_type ; 
 int /*<<< orphan*/  lpfc_sli_intf_if_type ; 
 int /*<<< orphan*/  lpfc_sli_intf_sli_family ; 
 int /*<<< orphan*/  lpfc_sli_intf_sli_hint1 ; 
 int /*<<< orphan*/  lpfc_sli_intf_sli_hint2 ; 
 int /*<<< orphan*/  lpfc_sli_intf_slirev ; 
 int /*<<< orphan*/  lpfc_sliport_status_err ; 
 int /*<<< orphan*/  lpfc_sliport_status_rn ; 
 int /*<<< orphan*/  memset (struct lpfc_register*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 void* readl (int /*<<< orphan*/ ) ; 

int
lpfc_sli4_post_status_check(struct lpfc_hba *phba)
{
	struct lpfc_register portsmphr_reg, uerrlo_reg, uerrhi_reg;
	struct lpfc_register reg_data;
	int i, port_error = 0;
	uint32_t if_type;

	memset(&portsmphr_reg, 0, sizeof(portsmphr_reg));
	memset(&reg_data, 0, sizeof(reg_data));
	if (!phba->sli4_hba.PSMPHRregaddr)
		return -ENODEV;

	/* Wait up to 30 seconds for the SLI Port POST done and ready */
	for (i = 0; i < 3000; i++) {
		if (lpfc_readl(phba->sli4_hba.PSMPHRregaddr,
			&portsmphr_reg.word0) ||
			(bf_get(lpfc_port_smphr_perr, &portsmphr_reg))) {
			/* Port has a fatal POST error, break out */
			port_error = -ENODEV;
			break;
		}
		if (LPFC_POST_STAGE_PORT_READY ==
		    bf_get(lpfc_port_smphr_port_status, &portsmphr_reg))
			break;
		msleep(10);
	}

	/*
	 * If there was a port error during POST, then don't proceed with
	 * other register reads as the data may not be valid.  Just exit.
	 */
	if (port_error) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"1408 Port Failed POST - portsmphr=0x%x, "
			"perr=x%x, sfi=x%x, nip=x%x, ipc=x%x, scr1=x%x, "
			"scr2=x%x, hscratch=x%x, pstatus=x%x\n",
			portsmphr_reg.word0,
			bf_get(lpfc_port_smphr_perr, &portsmphr_reg),
			bf_get(lpfc_port_smphr_sfi, &portsmphr_reg),
			bf_get(lpfc_port_smphr_nip, &portsmphr_reg),
			bf_get(lpfc_port_smphr_ipc, &portsmphr_reg),
			bf_get(lpfc_port_smphr_scr1, &portsmphr_reg),
			bf_get(lpfc_port_smphr_scr2, &portsmphr_reg),
			bf_get(lpfc_port_smphr_host_scratch, &portsmphr_reg),
			bf_get(lpfc_port_smphr_port_status, &portsmphr_reg));
	} else {
		lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
				"2534 Device Info: SLIFamily=0x%x, "
				"SLIRev=0x%x, IFType=0x%x, SLIHint_1=0x%x, "
				"SLIHint_2=0x%x, FT=0x%x\n",
				bf_get(lpfc_sli_intf_sli_family,
				       &phba->sli4_hba.sli_intf),
				bf_get(lpfc_sli_intf_slirev,
				       &phba->sli4_hba.sli_intf),
				bf_get(lpfc_sli_intf_if_type,
				       &phba->sli4_hba.sli_intf),
				bf_get(lpfc_sli_intf_sli_hint1,
				       &phba->sli4_hba.sli_intf),
				bf_get(lpfc_sli_intf_sli_hint2,
				       &phba->sli4_hba.sli_intf),
				bf_get(lpfc_sli_intf_func_type,
				       &phba->sli4_hba.sli_intf));
		/*
		 * Check for other Port errors during the initialization
		 * process.  Fail the load if the port did not come up
		 * correctly.
		 */
		if_type = bf_get(lpfc_sli_intf_if_type,
				 &phba->sli4_hba.sli_intf);
		switch (if_type) {
		case LPFC_SLI_INTF_IF_TYPE_0:
			phba->sli4_hba.ue_mask_lo =
			      readl(phba->sli4_hba.u.if_type0.UEMASKLOregaddr);
			phba->sli4_hba.ue_mask_hi =
			      readl(phba->sli4_hba.u.if_type0.UEMASKHIregaddr);
			uerrlo_reg.word0 =
			      readl(phba->sli4_hba.u.if_type0.UERRLOregaddr);
			uerrhi_reg.word0 =
				readl(phba->sli4_hba.u.if_type0.UERRHIregaddr);
			if ((~phba->sli4_hba.ue_mask_lo & uerrlo_reg.word0) ||
			    (~phba->sli4_hba.ue_mask_hi & uerrhi_reg.word0)) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"1422 Unrecoverable Error "
						"Detected during POST "
						"uerr_lo_reg=0x%x, "
						"uerr_hi_reg=0x%x, "
						"ue_mask_lo_reg=0x%x, "
						"ue_mask_hi_reg=0x%x\n",
						uerrlo_reg.word0,
						uerrhi_reg.word0,
						phba->sli4_hba.ue_mask_lo,
						phba->sli4_hba.ue_mask_hi);
				port_error = -ENODEV;
			}
			break;
		case LPFC_SLI_INTF_IF_TYPE_2:
			/* Final checks.  The port status should be clean. */
			if (lpfc_readl(phba->sli4_hba.u.if_type2.STATUSregaddr,
				&reg_data.word0) ||
				(bf_get(lpfc_sliport_status_err, &reg_data) &&
				 !bf_get(lpfc_sliport_status_rn, &reg_data))) {
				phba->work_status[0] =
					readl(phba->sli4_hba.u.if_type2.
					      ERR1regaddr);
				phba->work_status[1] =
					readl(phba->sli4_hba.u.if_type2.
					      ERR2regaddr);
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"2888 Unrecoverable port error "
					"following POST: port status reg "
					"0x%x, port_smphr reg 0x%x, "
					"error 1=0x%x, error 2=0x%x\n",
					reg_data.word0,
					portsmphr_reg.word0,
					phba->work_status[0],
					phba->work_status[1]);
				port_error = -ENODEV;
			}
			break;
		case LPFC_SLI_INTF_IF_TYPE_1:
		default:
			break;
		}
	}
	return port_error;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int suni_ds3_frm_stat; int suni_ds3_frm_intr_enbl; int suni_ds3_frm_cfg; int suni_ds3_tran_cfg; int suni_config; int suni_splr_cfg; int suni_splt_cfg; int suni_e3_frm_fram_intr_ind_stat; int suni_e3_frm_fram_options; int suni_e3_frm_maint_options; int suni_e3_frm_fram_intr_enbl; int suni_e3_frm_maint_intr_enbl; int suni_e3_tran_stat_diag_options; int suni_e3_tran_fram_options; int suni_intr_enbl; int suni_rxcp_ctrl; int suni_rxcp_fctrl; int suni_rxcp_idle_pat_h4; int suni_rxcp_idle_mask_h1; int suni_rxcp_idle_mask_h2; int suni_rxcp_idle_mask_h3; int suni_rxcp_idle_mask_h4; int suni_rxcp_cell_pat_h4; int suni_rxcp_cell_mask_h1; int suni_rxcp_cell_mask_h2; int suni_rxcp_cell_mask_h3; int suni_rxcp_cell_mask_h4; int suni_txcp_ctrl; int suni_txcp_intr_en_sts; int suni_txcp_idle_pat_h5; int /*<<< orphan*/  suni_rxcp_intr_en_sts; scalar_t__ suni_rxcp_cell_pat_h3; scalar_t__ suni_rxcp_cell_pat_h2; scalar_t__ suni_rxcp_cell_pat_h1; scalar_t__ suni_rxcp_idle_pat_h3; scalar_t__ suni_rxcp_idle_pat_h2; scalar_t__ suni_rxcp_idle_pat_h1; scalar_t__ suni_master_test; scalar_t__ suni_id_reset; } ;
typedef  TYPE_1__ suni_pm7345_t ;
struct TYPE_5__ {int phy_type; void* carrier_detect; scalar_t__ phy; } ;
typedef  TYPE_2__ IADEV ;

/* Variables and functions */
 void* Boolean (int) ; 
 int FE_DS3_PHY ; 
 int SUNI_DS3_LOSV ; 
 int SUNI_E3_LOS ; 
 int /*<<< orphan*/  SUNI_OOCDE ; 
 int SUNI_PM7345_CLB ; 
 int SUNI_PM7345_DLB ; 
 int SUNI_PM7345_E3ENBL ; 
 int SUNI_PM7345_LLB ; 
 int SUNI_PM7345_PLB ; 

__attribute__((used)) static void ia_suni_pm7345_init (IADEV *iadev)
{
   volatile suni_pm7345_t *suni_pm7345 = (suni_pm7345_t *)iadev->phy;
   if (iadev->phy_type & FE_DS3_PHY)
   {
      iadev->carrier_detect = 
          Boolean(!(suni_pm7345->suni_ds3_frm_stat & SUNI_DS3_LOSV)); 
      suni_pm7345->suni_ds3_frm_intr_enbl = 0x17;
      suni_pm7345->suni_ds3_frm_cfg = 1;
      suni_pm7345->suni_ds3_tran_cfg = 1;
      suni_pm7345->suni_config = 0;
      suni_pm7345->suni_splr_cfg = 0;
      suni_pm7345->suni_splt_cfg = 0;
   }
   else 
   {
      iadev->carrier_detect = 
          Boolean(!(suni_pm7345->suni_e3_frm_fram_intr_ind_stat & SUNI_E3_LOS));
      suni_pm7345->suni_e3_frm_fram_options = 0x4;
      suni_pm7345->suni_e3_frm_maint_options = 0x20;
      suni_pm7345->suni_e3_frm_fram_intr_enbl = 0x1d;
      suni_pm7345->suni_e3_frm_maint_intr_enbl = 0x30;
      suni_pm7345->suni_e3_tran_stat_diag_options = 0x0;
      suni_pm7345->suni_e3_tran_fram_options = 0x1;
      suni_pm7345->suni_config = SUNI_PM7345_E3ENBL;
      suni_pm7345->suni_splr_cfg = 0x41;
      suni_pm7345->suni_splt_cfg = 0x41;
   } 
   /*
    * Enable RSOP loss of signal interrupt.
    */
   suni_pm7345->suni_intr_enbl = 0x28;
 
   /*
    * Clear error counters
    */
   suni_pm7345->suni_id_reset = 0;

   /*
    * Clear "PMCTST" in master test register.
    */
   suni_pm7345->suni_master_test = 0;

   suni_pm7345->suni_rxcp_ctrl = 0x2c;
   suni_pm7345->suni_rxcp_fctrl = 0x81;
 
   suni_pm7345->suni_rxcp_idle_pat_h1 =
   	suni_pm7345->suni_rxcp_idle_pat_h2 =
   	suni_pm7345->suni_rxcp_idle_pat_h3 = 0;
   suni_pm7345->suni_rxcp_idle_pat_h4 = 1;
 
   suni_pm7345->suni_rxcp_idle_mask_h1 = 0xff;
   suni_pm7345->suni_rxcp_idle_mask_h2 = 0xff;
   suni_pm7345->suni_rxcp_idle_mask_h3 = 0xff;
   suni_pm7345->suni_rxcp_idle_mask_h4 = 0xfe;
 
   suni_pm7345->suni_rxcp_cell_pat_h1 =
   	suni_pm7345->suni_rxcp_cell_pat_h2 =
   	suni_pm7345->suni_rxcp_cell_pat_h3 = 0;
   suni_pm7345->suni_rxcp_cell_pat_h4 = 1;
 
   suni_pm7345->suni_rxcp_cell_mask_h1 =
   	suni_pm7345->suni_rxcp_cell_mask_h2 =
   	suni_pm7345->suni_rxcp_cell_mask_h3 =
   	suni_pm7345->suni_rxcp_cell_mask_h4 = 0xff;
 
   suni_pm7345->suni_txcp_ctrl = 0xa4;
   suni_pm7345->suni_txcp_intr_en_sts = 0x10;
   suni_pm7345->suni_txcp_idle_pat_h5 = 0x55;
 
   suni_pm7345->suni_config &= ~(SUNI_PM7345_LLB |
                                 SUNI_PM7345_CLB |
                                 SUNI_PM7345_DLB |
                                  SUNI_PM7345_PLB);
#ifdef __SNMP__
   suni_pm7345->suni_rxcp_intr_en_sts |= SUNI_OOCDE;
#endif /* __SNMP__ */
   return;
}
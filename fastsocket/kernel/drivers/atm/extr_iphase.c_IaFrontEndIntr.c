#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int u32 ;
struct TYPE_6__ {int suni_ds3_frm_stat; int suni_e3_frm_fram_intr_ind_stat; int /*<<< orphan*/  suni_e3_frm_maint_intr_ind; int /*<<< orphan*/  suni_ds3_frm_intr_stat; } ;
typedef  TYPE_1__ suni_pm7345_t ;
struct TYPE_7__ {int mb25_intr_status; } ;
typedef  TYPE_2__ ia_mb25_t ;
struct TYPE_9__ {int phy_type; void* carrier_detect; scalar_t__ phy; } ;
struct TYPE_8__ {int suni_rsop_status; } ;
typedef  TYPE_3__ IA_SUNI ;
typedef  TYPE_4__ IADEV ;

/* Variables and functions */
 void* Boolean (int) ; 
 int FE_25MBIT_PHY ; 
 int FE_DS3_PHY ; 
 int FE_E3_PHY ; 
 int MB25_IS_GSB ; 
 int SUNI_DS3_LOSV ; 
 int SUNI_E3_LOS ; 
 int SUNI_LOSV ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void IaFrontEndIntr(IADEV *iadev) {
  volatile IA_SUNI *suni;
  volatile ia_mb25_t *mb25;
  volatile suni_pm7345_t *suni_pm7345;
  u32 intr_status;
  u_int frmr_intr;

  if(iadev->phy_type & FE_25MBIT_PHY) {
     mb25 = (ia_mb25_t*)iadev->phy;
     iadev->carrier_detect =  Boolean(mb25->mb25_intr_status & MB25_IS_GSB);
  } else if (iadev->phy_type & FE_DS3_PHY) {
     suni_pm7345 = (suni_pm7345_t *)iadev->phy;
     /* clear FRMR interrupts */
     frmr_intr   = suni_pm7345->suni_ds3_frm_intr_stat; 
     iadev->carrier_detect =  
           Boolean(!(suni_pm7345->suni_ds3_frm_stat & SUNI_DS3_LOSV));
  } else if (iadev->phy_type & FE_E3_PHY ) {
     suni_pm7345 = (suni_pm7345_t *)iadev->phy;
     frmr_intr   = suni_pm7345->suni_e3_frm_maint_intr_ind;
     iadev->carrier_detect =
           Boolean(!(suni_pm7345->suni_e3_frm_fram_intr_ind_stat&SUNI_E3_LOS));
  }
  else { 
     suni = (IA_SUNI *)iadev->phy;
     intr_status = suni->suni_rsop_status & 0xff;
     iadev->carrier_detect = Boolean(!(suni->suni_rsop_status & SUNI_LOSV));
  }
  if (iadev->carrier_detect)
    printk("IA: SUNI carrier detected\n");
  else
    printk("IA: SUNI carrier lost signal\n"); 
  return;
}
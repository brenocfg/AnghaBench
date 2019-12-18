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
typedef  void* u_long ;
struct TYPE_9__ {void* t_pri; void* t_neg; } ;
struct TYPE_8__ {scalar_t__ s2u; scalar_t__ s2l; void* fm_st3l; void* fm_st3u; void* fm_st2l; void* fm_st2u; void* fm_st1l; void* fm_st1u; int /*<<< orphan*/  mdr3init; scalar_t__ frselreg_init; scalar_t__ func_addr; int /*<<< orphan*/  group_addr; int /*<<< orphan*/  rx_mode; int /*<<< orphan*/  nsa_mode; } ;
struct TYPE_7__ {scalar_t__ mac_r_restart_counter; scalar_t__ mac_nobuf_counter; } ;
struct TYPE_10__ {TYPE_4__ mac_pa; scalar_t__ mac_ring_is_up; TYPE_3__ fp; TYPE_2__ mac_ct; } ;
struct TYPE_6__ {scalar_t__ sas; } ;
struct s_smc {TYPE_5__ hw; TYPE_1__ s; } ;
typedef  void* HW_PTR ;

/* Variables and functions */
 scalar_t__ ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B0_ST1L ; 
 int /*<<< orphan*/  B0_ST1U ; 
 int /*<<< orphan*/  B0_ST2L ; 
 int /*<<< orphan*/  B0_ST2U ; 
 int /*<<< orphan*/  B0_ST3L ; 
 int /*<<< orphan*/  B0_ST3U ; 
 int /*<<< orphan*/  FM_MDAMA ; 
 int /*<<< orphan*/  FM_MENDAS ; 
 int /*<<< orphan*/  FM_MRNNSAFNMA ; 
 scalar_t__ SMT_DAS ; 
 int /*<<< orphan*/  fddi_broadcast ; 
 int /*<<< orphan*/  init_driver_fplus (struct s_smc*) ; 
 int init_mac (struct s_smc*,int) ; 
 int /*<<< orphan*/  mac_counter_init (struct s_smc*) ; 
 int /*<<< orphan*/  mac_do_pci_fix (struct s_smc*) ; 

int init_fplus(struct s_smc *smc)
{
	smc->hw.fp.nsa_mode = FM_MRNNSAFNMA ;
	smc->hw.fp.rx_mode = FM_MDAMA ;
	smc->hw.fp.group_addr = fddi_broadcast ;
	smc->hw.fp.func_addr = 0 ;
	smc->hw.fp.frselreg_init = 0 ;

	init_driver_fplus(smc) ;
	if (smc->s.sas == SMT_DAS)
		smc->hw.fp.mdr3init |= FM_MENDAS ;

	smc->hw.mac_ct.mac_nobuf_counter = 0 ;
	smc->hw.mac_ct.mac_r_restart_counter = 0 ;

	smc->hw.fp.fm_st1u = (HW_PTR) ADDR(B0_ST1U) ;
	smc->hw.fp.fm_st1l = (HW_PTR) ADDR(B0_ST1L) ;
	smc->hw.fp.fm_st2u = (HW_PTR) ADDR(B0_ST2U) ;
	smc->hw.fp.fm_st2l = (HW_PTR) ADDR(B0_ST2L) ;
	smc->hw.fp.fm_st3u = (HW_PTR) ADDR(B0_ST3U) ;
	smc->hw.fp.fm_st3l = (HW_PTR) ADDR(B0_ST3L) ;

	smc->hw.fp.s2l = smc->hw.fp.s2u = 0 ;
	smc->hw.mac_ring_is_up = 0 ;

	mac_counter_init(smc) ;

	/* convert BCKL units to symbol time */
	smc->hw.mac_pa.t_neg = (u_long)0 ;
	smc->hw.mac_pa.t_pri = (u_long)0 ;

	/* make sure all PCI settings are correct */
	mac_do_pci_fix(smc) ;

	return(init_mac(smc,1)) ;
	/* enable_formac(smc) ; */
}
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
struct smt_p_mac_status {int /*<<< orphan*/  st_lost_ct; int /*<<< orphan*/  st_error_ct; int /*<<< orphan*/  st_frame_ct; int /*<<< orphan*/  st_sba; int /*<<< orphan*/  st_t_min; int /*<<< orphan*/  st_tvx_value; int /*<<< orphan*/  st_t_max; int /*<<< orphan*/  st_t_neg; int /*<<< orphan*/  st_t_req; int /*<<< orphan*/  st_mac_index; int /*<<< orphan*/  st_mib_index; } ;
struct TYPE_6__ {TYPE_2__* m; TYPE_1__* a; } ;
struct s_smc {TYPE_3__ mib; } ;
struct TYPE_5__ {int /*<<< orphan*/  fddiMACLost_Ct; int /*<<< orphan*/  fddiMACError_Ct; int /*<<< orphan*/  fddiMACFrame_Ct; int /*<<< orphan*/  fddiMACT_Min; int /*<<< orphan*/  fddiMACTvxValue; int /*<<< orphan*/  fddiMACT_Max; int /*<<< orphan*/  fddiMACT_Neg; int /*<<< orphan*/  fddiMACT_Req; } ;
struct TYPE_4__ {int /*<<< orphan*/  fddiPATHSbaPayload; } ;

/* Variables and functions */
 int /*<<< orphan*/  INDEX_MAC ; 
 size_t MAC0 ; 
 size_t PATH0 ; 
 int /*<<< orphan*/  SMTSETPARA (struct smt_p_mac_status*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMT_P_MAC_STATUS ; 
 int /*<<< orphan*/  mac_index (struct s_smc*,int) ; 
 int /*<<< orphan*/  mac_update_counter (struct s_smc*) ; 

__attribute__((used)) static void smt_fill_mac_status(struct s_smc *smc, struct smt_p_mac_status *st)
{
	SMTSETPARA(st,SMT_P_MAC_STATUS) ;

	st->st_mib_index = INDEX_MAC ;
	st->st_mac_index = mac_index(smc,1) ;

	mac_update_counter(smc) ;
	/*
	 * timer values are represented in SMT as 2's complement numbers
	 * units :	internal :  2's complement BCLK
	 */
	st->st_t_req = smc->mib.m[MAC0].fddiMACT_Req ;
	st->st_t_neg = smc->mib.m[MAC0].fddiMACT_Neg ;
	st->st_t_max = smc->mib.m[MAC0].fddiMACT_Max ;
	st->st_tvx_value = smc->mib.m[MAC0].fddiMACTvxValue ;
	st->st_t_min = smc->mib.m[MAC0].fddiMACT_Min ;

	st->st_sba = smc->mib.a[PATH0].fddiPATHSbaPayload ;
	st->st_frame_ct = smc->mib.m[MAC0].fddiMACFrame_Ct ;
	st->st_error_ct = smc->mib.m[MAC0].fddiMACError_Ct ;
	st->st_lost_ct = smc->mib.m[MAC0].fddiMACLost_Ct ;
}
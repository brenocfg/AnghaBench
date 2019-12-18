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
struct TYPE_5__ {int /*<<< orphan*/  no_flag; scalar_t__ jm_flag; scalar_t__ bn_flag; scalar_t__ loop_avail; void* sm_ma_avail; scalar_t__ da_flag; int /*<<< orphan*/  dup_addr_test; } ;
struct TYPE_4__ {TYPE_3__* m; } ;
struct s_smc {TYPE_2__ r; TYPE_1__ mib; } ;
struct TYPE_6__ {void* fddiMACMA_UnitdataAvailable; int /*<<< orphan*/  fddiMACRMTState; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIONS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DA_NONE ; 
 void* FALSE ; 
 size_t MAC0 ; 
 int /*<<< orphan*/  RM0_ISOLATED ; 
 int /*<<< orphan*/  TRUE ; 

void rmt_init(struct s_smc *smc)
{
	smc->mib.m[MAC0].fddiMACRMTState = ACTIONS(RM0_ISOLATED) ;
	smc->r.dup_addr_test = DA_NONE ;
	smc->r.da_flag = 0 ;
	smc->mib.m[MAC0].fddiMACMA_UnitdataAvailable = FALSE ;
	smc->r.sm_ma_avail = FALSE ;
	smc->r.loop_avail = 0 ;
	smc->r.bn_flag = 0 ;
	smc->r.jm_flag = 0 ;
	smc->r.no_flag = TRUE ;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rmt_dup_mac_behavior; } ;
struct TYPE_3__ {scalar_t__ jm_flag; } ;
struct s_smc {TYPE_2__ s; TYPE_1__ r; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMT_E0135 ; 
 int /*<<< orphan*/  SMT_E0135_MSG ; 
 int /*<<< orphan*/  SMT_E0138 ; 
 int /*<<< orphan*/  SMT_E0138_MSG ; 
 int /*<<< orphan*/  SMT_ERR_LOG (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmt_leave_actions (struct s_smc*) ; 
 int /*<<< orphan*/  rmt_reinsert_actions (struct s_smc*) ; 

__attribute__((used)) static void rmt_dup_actions(struct s_smc *smc)
{
	if (smc->r.jm_flag) {
	}
	else {
		if (smc->s.rmt_dup_mac_behavior) {
			SMT_ERR_LOG(smc,SMT_E0138, SMT_E0138_MSG) ;
                        rmt_reinsert_actions(smc) ;
		}
		else {
			SMT_ERR_LOG(smc,SMT_E0135, SMT_E0135_MSG) ;
			rmt_leave_actions(smc) ;
		}
	}
}
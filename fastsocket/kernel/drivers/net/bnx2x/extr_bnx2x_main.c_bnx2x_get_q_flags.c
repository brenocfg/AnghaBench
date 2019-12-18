#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bnx2x_fastpath {scalar_t__ mode; int /*<<< orphan*/  disable_tpa; } ;
struct bnx2x {scalar_t__ vlgrp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_Q_FLG_FCOE ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_FORCE_DEFAULT_PRI ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_LEADING_RSS ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_MCAST ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_OV ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_SILENT_VLAN_REM ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_TPA ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_TPA_GRO ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_TPA_IPV6 ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_VLAN ; 
 scalar_t__ IS_FCOE_FP (struct bnx2x_fastpath*) ; 
 scalar_t__ IS_MF_AFEX (struct bnx2x*) ; 
 scalar_t__ IS_MF_SD (struct bnx2x*) ; 
 scalar_t__ TPA_MODE_GRO ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 unsigned long bnx2x_get_common_flags (struct bnx2x*,struct bnx2x_fastpath*,int) ; 

__attribute__((used)) static unsigned long bnx2x_get_q_flags(struct bnx2x *bp,
				       struct bnx2x_fastpath *fp,
				       bool leading)
{
	unsigned long flags = 0;

	/* calculate other queue flags */
	if (IS_MF_SD(bp))
		__set_bit(BNX2X_Q_FLG_OV, &flags);

	if (IS_FCOE_FP(fp)) {
		__set_bit(BNX2X_Q_FLG_FCOE, &flags);
		/* For FCoE - force usage of default priority (for afex) */
		__set_bit(BNX2X_Q_FLG_FORCE_DEFAULT_PRI, &flags);
	}

	if (!fp->disable_tpa) {
		__set_bit(BNX2X_Q_FLG_TPA, &flags);
		__set_bit(BNX2X_Q_FLG_TPA_IPV6, &flags);
		if (fp->mode == TPA_MODE_GRO)
			__set_bit(BNX2X_Q_FLG_TPA_GRO, &flags);
	}

	if (leading) {
		__set_bit(BNX2X_Q_FLG_LEADING_RSS, &flags);
		__set_bit(BNX2X_Q_FLG_MCAST, &flags);
	}

	if (bp->vlgrp)
		__set_bit(BNX2X_Q_FLG_VLAN, &flags);

	/* configure silent vlan removal */
	if (IS_MF_AFEX(bp))
		__set_bit(BNX2X_Q_FLG_SILENT_VLAN_REM, &flags);

	return flags | bnx2x_get_common_flags(bp, fp, true);
}
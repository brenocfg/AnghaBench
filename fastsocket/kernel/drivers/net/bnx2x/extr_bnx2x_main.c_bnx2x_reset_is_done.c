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
typedef  int u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_PATH0_RST_IN_PROG_BIT ; 
 int BNX2X_PATH1_RST_IN_PROG_BIT ; 
 int /*<<< orphan*/  BNX2X_RECOVERY_GLOB_REG ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 

bool bnx2x_reset_is_done(struct bnx2x *bp, int engine)
{
	u32 val = REG_RD(bp, BNX2X_RECOVERY_GLOB_REG);
	u32 bit = engine ?
		BNX2X_PATH1_RST_IN_PROG_BIT : BNX2X_PATH0_RST_IN_PROG_BIT;

	/* return false if bit is set */
	return (val & bit) ? false : true;
}
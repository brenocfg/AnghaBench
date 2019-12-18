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
typedef  int u8 ;
typedef  int u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MISC_REG_PORT4MODE_EN ; 
 int /*<<< orphan*/  MISC_REG_PORT4MODE_EN_OVWR ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 bnx2x_is_4_port_mode(struct bnx2x *bp)
{
	u32 port4mode_ovwr_val;
	/* Check 4-port override enabled */
	port4mode_ovwr_val = REG_RD(bp, MISC_REG_PORT4MODE_EN_OVWR);
	if (port4mode_ovwr_val & (1<<0)) {
		/* Return 4-port mode override value */
		return ((port4mode_ovwr_val & (1<<1)) == (1<<1));
	}
	/* Return 4-port mode from input pin */
	return (u8)REG_RD(bp, MISC_REG_PORT4MODE_EN);
}
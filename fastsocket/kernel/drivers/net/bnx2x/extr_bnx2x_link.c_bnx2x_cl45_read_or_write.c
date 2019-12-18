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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void bnx2x_cl45_read_or_write(struct bnx2x *bp, struct bnx2x_phy *phy,
				     u8 devad, u16 reg, u16 or_val)
{
	u16 val;
	bnx2x_cl45_read(bp, phy, devad, reg, &val);
	bnx2x_cl45_write(bp, phy, devad, reg, val | or_val);
}
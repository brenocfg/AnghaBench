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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_CSTRORM_INTMEM ; 
 scalar_t__ CSTORM_EVENT_RING_PROD_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR16 (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void storm_memset_eq_prod(struct bnx2x *bp, u16 eq_prod,
				 u16 pfid)
{
	u32 addr = BAR_CSTRORM_INTMEM + CSTORM_EVENT_RING_PROD_OFFSET(pfid);
	REG_WR16(bp, addr, eq_prod);
}
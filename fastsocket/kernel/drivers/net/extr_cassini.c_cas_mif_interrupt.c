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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct cas {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ CAS_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIF_STATUS_POLL_DATA ; 
 int /*<<< orphan*/  MIF_STATUS_POLL_STATUS ; 
 scalar_t__ REG_MIF_STATUS ; 
 int cas_mii_link_check (struct cas*,scalar_t__) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int cas_mif_interrupt(struct net_device *dev, struct cas *cp,
			     u32 status)
{
	u32 stat = readl(cp->regs + REG_MIF_STATUS);
	u16 bmsr;

	/* check for a link change */
	if (CAS_VAL(MIF_STATUS_POLL_STATUS, stat) == 0)
		return 0;

	bmsr = CAS_VAL(MIF_STATUS_POLL_DATA, stat);
	return cas_mii_link_check(cp, bmsr);
}
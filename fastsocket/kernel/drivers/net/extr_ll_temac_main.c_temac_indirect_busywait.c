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
struct temac_local {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int XTE_RDY0_HARD_ACS_RDY_MASK ; 
 int /*<<< orphan*/  XTE_RDY0_OFFSET ; 
 int jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int temac_ior (struct temac_local*,int /*<<< orphan*/ ) ; 

int temac_indirect_busywait(struct temac_local *lp)
{
	long end = jiffies + 2;

	while (!(temac_ior(lp, XTE_RDY0_OFFSET) & XTE_RDY0_HARD_ACS_RDY_MASK)) {
		if (end - jiffies <= 0) {
			WARN_ON(1);
			return -ETIMEDOUT;
		}
		msleep(1);
	}
	return 0;
}
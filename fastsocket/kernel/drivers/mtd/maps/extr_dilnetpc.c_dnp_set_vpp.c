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
struct map_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CSC_RBWR ; 
 int /*<<< orphan*/  dnpc_spin ; 
 int getcsc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setcsc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int vpp_counter ; 

__attribute__((used)) static void dnp_set_vpp(struct map_info *not_used, int on)
{
	spin_lock_irq(&dnpc_spin);

	if (on)
	{
		if(++vpp_counter == 1)
			setcsc(CSC_RBWR, getcsc(CSC_RBWR) & ~0x4);
	}
	else
	{
		if(--vpp_counter == 0)
			setcsc(CSC_RBWR, getcsc(CSC_RBWR) | 0x4);
		else
			BUG_ON(vpp_counter < 0);
	}
	spin_unlock_irq(&dnpc_spin);
}
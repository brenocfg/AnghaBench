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
struct pdc_system_map_addr_info {int /*<<< orphan*/  mod_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDC_FIND_ADDRESS ; 
 int /*<<< orphan*/  PDC_SYSTEM_MAP ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_wide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_extend (int /*<<< orphan*/ ) ; 
 int mem_pdc_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,long) ; 
 int /*<<< orphan*/  memcpy (struct pdc_system_map_addr_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdc_lock ; 
 int /*<<< orphan*/  pdc_result ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pdc_system_map_find_addrs(struct pdc_system_map_addr_info *pdc_addr_info, 
			      long mod_index, long addr_index)
{
	int retval;
	unsigned long flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_SYSTEM_MAP, PDC_FIND_ADDRESS, __pa(pdc_result),
			      mod_index, addr_index);
	convert_to_wide(pdc_result);
	memcpy(pdc_addr_info, pdc_result, sizeof(*pdc_addr_info));
	spin_unlock_irqrestore(&pdc_lock, flags);

	pdc_addr_info->mod_addr = f_extend(pdc_addr_info->mod_addr);
	return retval;
}
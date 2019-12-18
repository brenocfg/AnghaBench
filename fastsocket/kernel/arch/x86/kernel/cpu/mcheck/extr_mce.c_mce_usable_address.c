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
struct mce {int status; int /*<<< orphan*/  misc; } ;

/* Variables and functions */
 scalar_t__ MCI_MISC_ADDR_LSB (int /*<<< orphan*/ ) ; 
 scalar_t__ MCI_MISC_ADDR_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MCI_MISC_ADDR_PHYS ; 
 int MCI_STATUS_ADDRV ; 
 int MCI_STATUS_MISCV ; 
 scalar_t__ PAGE_SHIFT ; 

__attribute__((used)) static int mce_usable_address(struct mce *m)
{
	if (!(m->status & MCI_STATUS_MISCV) || !(m->status & MCI_STATUS_ADDRV))
		return 0;
	if (MCI_MISC_ADDR_LSB(m->misc) > PAGE_SHIFT)
		return 0;
	if (MCI_MISC_ADDR_MODE(m->misc) != MCI_MISC_ADDR_PHYS)
		return 0;
	return 1;
}
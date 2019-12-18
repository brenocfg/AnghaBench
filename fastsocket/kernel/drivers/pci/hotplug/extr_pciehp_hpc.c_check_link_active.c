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
typedef  int u16 ;
struct controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 int PCI_EXP_LNKSTA_DLLLA ; 
 scalar_t__ pciehp_readw (struct controller*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline int check_link_active(struct controller *ctrl)
{
	u16 link_status;

	if (pciehp_readw(ctrl, PCI_EXP_LNKSTA, &link_status))
		return 0;
	return !!(link_status & PCI_EXP_LNKSTA_DLLLA);
}
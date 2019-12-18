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
struct edac_pci_ctl_info {int /*<<< orphan*/  rcu; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_edac_pci_list_del ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_barrier () ; 

__attribute__((used)) static void del_edac_pci_from_global_list(struct edac_pci_ctl_info *pci)
{
	list_del_rcu(&pci->link);
	call_rcu(&pci->rcu, complete_edac_pci_list_del);
	rcu_barrier();
}
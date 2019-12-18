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
struct pcie_link_state {struct pcie_link_state* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcie_config_aspm_link (struct pcie_link_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_to_aspm_state (struct pcie_link_state*) ; 

__attribute__((used)) static void pcie_config_aspm_path(struct pcie_link_state *link)
{
	while (link) {
		pcie_config_aspm_link(link, policy_to_aspm_state(link));
		link = link->parent;
	}
}
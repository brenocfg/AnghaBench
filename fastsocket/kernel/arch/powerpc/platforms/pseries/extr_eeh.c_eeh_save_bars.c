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
struct pci_dn {int /*<<< orphan*/ * config_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtas_read_config (struct pci_dn*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eeh_save_bars(struct pci_dn *pdn)
{
	int i;

	if (!pdn )
		return;
	
	for (i = 0; i < 16; i++)
		rtas_read_config(pdn, i * 4, 4, &pdn->config_space[i]);
}
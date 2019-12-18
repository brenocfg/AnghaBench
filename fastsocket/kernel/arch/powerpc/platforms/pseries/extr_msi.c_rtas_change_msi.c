#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dn {TYPE_1__* phb; int /*<<< orphan*/  devfn; int /*<<< orphan*/  busno; } ;
struct TYPE_2__ {unsigned long buid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUID_HI (unsigned long) ; 
 int /*<<< orphan*/  BUID_LO (unsigned long) ; 
 int RTAS_CHANGE_MSIX_FN ; 
 int RTAS_CHANGE_MSI_FN ; 
 int /*<<< orphan*/  change_token ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int) ; 
 scalar_t__ rtas_busy_delay (int) ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int rtas_config_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtas_change_msi(struct pci_dn *pdn, u32 func, u32 num_irqs)
{
	u32 addr, seq_num, rtas_ret[3];
	unsigned long buid;
	int rc;

	addr = rtas_config_addr(pdn->busno, pdn->devfn, 0);
	buid = pdn->phb->buid;

	seq_num = 1;
	do {
		if (func == RTAS_CHANGE_MSI_FN || func == RTAS_CHANGE_MSIX_FN)
			rc = rtas_call(change_token, 6, 4, rtas_ret, addr,
					BUID_HI(buid), BUID_LO(buid),
					func, num_irqs, seq_num);
		else
			rc = rtas_call(change_token, 6, 3, rtas_ret, addr,
					BUID_HI(buid), BUID_LO(buid),
					func, num_irqs, seq_num);

		seq_num = rtas_ret[1];
	} while (rtas_busy_delay(rc));

	/*
	 * If the RTAS call succeeded, return the number of irqs allocated.
	 * If not, make sure we return a negative error code.
	 */
	if (rc == 0)
		rc = rtas_ret[0];
	else if (rc > 0)
		rc = -rc;

	pr_debug("rtas_msi: ibm,change_msi(func=%d,num=%d), got %d rc = %d\n",
		 func, num_irqs, rtas_ret[0], rc);

	return rc;
}
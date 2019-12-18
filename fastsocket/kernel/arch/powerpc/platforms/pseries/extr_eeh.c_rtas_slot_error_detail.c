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
struct pci_dn {int eeh_config_addr; int eeh_pe_config_addr; TYPE_1__* phb; } ;
struct TYPE_2__ {int /*<<< orphan*/  buid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUID_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUID_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_TYPE_RTAS_LOG ; 
 int /*<<< orphan*/  eeh_error_buf_size ; 
 int /*<<< orphan*/  ibm_slot_error_detail ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* slot_errbuf ; 
 int /*<<< orphan*/  slot_errbuf_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virt_to_phys (char*) ; 

__attribute__((used)) static void rtas_slot_error_detail(struct pci_dn *pdn, int severity,
                                   char *driver_log, size_t loglen)
{
	int config_addr;
	unsigned long flags;
	int rc;

	/* Log the error with the rtas logger */
	spin_lock_irqsave(&slot_errbuf_lock, flags);
	memset(slot_errbuf, 0, eeh_error_buf_size);

	/* Use PE configuration address, if present */
	config_addr = pdn->eeh_config_addr;
	if (pdn->eeh_pe_config_addr)
		config_addr = pdn->eeh_pe_config_addr;

	rc = rtas_call(ibm_slot_error_detail,
	               8, 1, NULL, config_addr,
	               BUID_HI(pdn->phb->buid),
	               BUID_LO(pdn->phb->buid),
	               virt_to_phys(driver_log), loglen,
	               virt_to_phys(slot_errbuf),
	               eeh_error_buf_size,
	               severity);

	if (rc == 0)
		log_error(slot_errbuf, ERR_TYPE_RTAS_LOG, 0);
	spin_unlock_irqrestore(&slot_errbuf_lock, flags);
}
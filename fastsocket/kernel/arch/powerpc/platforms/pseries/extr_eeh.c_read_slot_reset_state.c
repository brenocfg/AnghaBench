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
 int RTAS_UNKNOWN_SERVICE ; 
 int ibm_read_slot_reset_state ; 
 int ibm_read_slot_reset_state2 ; 
 int rtas_call (int,int,int,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_slot_reset_state(struct pci_dn *pdn, int rets[])
{
	int token, outputs;
	int config_addr;

	if (ibm_read_slot_reset_state2 != RTAS_UNKNOWN_SERVICE) {
		token = ibm_read_slot_reset_state2;
		outputs = 4;
	} else {
		token = ibm_read_slot_reset_state;
		rets[2] = 0; /* fake PE Unavailable info */
		outputs = 3;
	}

	/* Use PE configuration address, if present */
	config_addr = pdn->eeh_config_addr;
	if (pdn->eeh_pe_config_addr)
		config_addr = pdn->eeh_pe_config_addr;

	return rtas_call(token, 3, outputs, rets, config_addr,
			 BUID_HI(pdn->phb->buid), BUID_LO(pdn->phb->buid));
}
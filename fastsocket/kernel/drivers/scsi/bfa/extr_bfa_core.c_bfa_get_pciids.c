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
struct bfa_pciid_s {int /*<<< orphan*/  member_1; int /*<<< orphan*/  const member_0; } ;
typedef  int /*<<< orphan*/  __pciids ;

/* Variables and functions */
#define  BFA_PCI_DEVICE_ID_CT 132 
#define  BFA_PCI_DEVICE_ID_CT_FC 131 
#define  BFA_PCI_DEVICE_ID_FC_8G1P 130 
#define  BFA_PCI_DEVICE_ID_FC_8G2P 129 
#define  BFA_PCI_VENDOR_ID_BROCADE 128 

void
bfa_get_pciids(struct bfa_pciid_s **pciids, int *npciids)
{
	static struct bfa_pciid_s __pciids[] = {
		{BFA_PCI_VENDOR_ID_BROCADE, BFA_PCI_DEVICE_ID_FC_8G2P},
		{BFA_PCI_VENDOR_ID_BROCADE, BFA_PCI_DEVICE_ID_FC_8G1P},
		{BFA_PCI_VENDOR_ID_BROCADE, BFA_PCI_DEVICE_ID_CT},
		{BFA_PCI_VENDOR_ID_BROCADE, BFA_PCI_DEVICE_ID_CT_FC},
	};

	*npciids = sizeof(__pciids) / sizeof(__pciids[0]);
	*pciids = __pciids;
}
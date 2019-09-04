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
typedef  int /*<<< orphan*/  IKE_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  IKE_VENDOR_ID_IPSEC_NAT_T_IKE_00 ; 
 int /*<<< orphan*/  IKE_VENDOR_ID_IPSEC_NAT_T_IKE_02 ; 
 int /*<<< orphan*/  IKE_VENDOR_ID_IPSEC_NAT_T_IKE_02_2 ; 
 int /*<<< orphan*/  IKE_VENDOR_ID_IPSEC_NAT_T_IKE_03 ; 
 int /*<<< orphan*/  IKE_VENDOR_ID_RFC3706_DPD ; 
 int /*<<< orphan*/  IKE_VENDOR_ID_RFC3947_NAT_T ; 
 int /*<<< orphan*/  IkeAddVendorId (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void IkeAddVendorIdPayloads(IKE_PACKET *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	IkeAddVendorId(p, IKE_VENDOR_ID_RFC3947_NAT_T);
	IkeAddVendorId(p, IKE_VENDOR_ID_IPSEC_NAT_T_IKE_03);
	IkeAddVendorId(p, IKE_VENDOR_ID_IPSEC_NAT_T_IKE_02);
	IkeAddVendorId(p, IKE_VENDOR_ID_IPSEC_NAT_T_IKE_02_2);
	IkeAddVendorId(p, IKE_VENDOR_ID_IPSEC_NAT_T_IKE_00);
	IkeAddVendorId(p, IKE_VENDOR_ID_RFC3706_DPD);
}
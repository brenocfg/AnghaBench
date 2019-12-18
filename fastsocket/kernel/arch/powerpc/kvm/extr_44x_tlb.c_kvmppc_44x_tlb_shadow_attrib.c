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
typedef  int u32 ;

/* Variables and functions */
 int PPC44x_TLB_M ; 
 int PPC44x_TLB_PERM_MASK ; 
 int PPC44x_TLB_SR ; 
 int PPC44x_TLB_SUPER_PERM_MASK ; 
 int PPC44x_TLB_SW ; 
 int PPC44x_TLB_SX ; 
 int PPC44x_TLB_UATTR_MASK ; 
 int PPC44x_TLB_USER_PERM_MASK ; 

__attribute__((used)) static u32 kvmppc_44x_tlb_shadow_attrib(u32 attrib, int usermode)
{
	/* We only care about the guest's permission and user bits. */
	attrib &= PPC44x_TLB_PERM_MASK|PPC44x_TLB_UATTR_MASK;

	if (!usermode) {
		/* Guest is in supervisor mode, so we need to translate guest
		 * supervisor permissions into user permissions. */
		attrib &= ~PPC44x_TLB_USER_PERM_MASK;
		attrib |= (attrib & PPC44x_TLB_SUPER_PERM_MASK) << 3;
	}

	/* Make sure host can always access this memory. */
	attrib |= PPC44x_TLB_SX|PPC44x_TLB_SR|PPC44x_TLB_SW;

	/* WIMGE = 0b00100 */
	attrib |= PPC44x_TLB_M;

	return attrib;
}
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
typedef  int u64 ;

/* Variables and functions */
 int _PAGE_PPN_MASK ; 
 int kvm_get_mpt_entry (int) ; 

u64 kvm_lookup_mpa(u64 gpfn)
{
	u64 maddr;
	maddr = kvm_get_mpt_entry(gpfn);
	return maddr&_PAGE_PPN_MASK;
}
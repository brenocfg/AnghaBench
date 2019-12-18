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
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int kvm_lookup_mpa (int) ; 

u64 kvm_gpa_to_mpa(u64 gpa)
{
	u64 pte = kvm_lookup_mpa(gpa >> PAGE_SHIFT);
	return (pte >> PAGE_SHIFT << PAGE_SHIFT) | (gpa & ~PAGE_MASK);
}
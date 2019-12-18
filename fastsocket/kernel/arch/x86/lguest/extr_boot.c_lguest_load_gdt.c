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
struct desc_struct {int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct desc_ptr {int size; scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  LHCALL_LOAD_GDT_ENTRY ; 
 int /*<<< orphan*/  kvm_hypercall3 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lguest_load_gdt(const struct desc_ptr *desc)
{
	unsigned int i;
	struct desc_struct *gdt = (void *)desc->address;

	for (i = 0; i < (desc->size+1)/8; i++)
		kvm_hypercall3(LHCALL_LOAD_GDT_ENTRY, i, gdt[i].a, gdt[i].b);
}
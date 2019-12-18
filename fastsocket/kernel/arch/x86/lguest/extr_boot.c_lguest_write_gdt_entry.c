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

/* Variables and functions */
 int /*<<< orphan*/  LHCALL_LOAD_GDT_ENTRY ; 
 int /*<<< orphan*/  kvm_hypercall3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  native_write_gdt_entry (struct desc_struct*,int,void const*,int) ; 

__attribute__((used)) static void lguest_write_gdt_entry(struct desc_struct *dt, int entrynum,
				   const void *desc, int type)
{
	native_write_gdt_entry(dt, entrynum, desc, type);
	/* Tell Host about this new entry. */
	kvm_hypercall3(LHCALL_LOAD_GDT_ENTRY, entrynum,
		       dt[entrynum].a, dt[entrynum].b);
}
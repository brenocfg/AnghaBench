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
struct descriptor_table {scalar_t__ base; } ;
struct desc_struct {int type; } ;

/* Variables and functions */
 size_t GDT_ENTRY_TSS ; 
 int /*<<< orphan*/  kvm_get_gdt (struct descriptor_table*) ; 
 int /*<<< orphan*/  load_TR_desc () ; 

__attribute__((used)) static void reload_tss(void)
{
	/*
	 * VT restores TR but not its size.  Useless.
	 */
	struct descriptor_table gdt;
	struct desc_struct *descs;

	kvm_get_gdt(&gdt);
	descs = (void *)gdt.base;
	descs[GDT_ENTRY_TSS].type = 9; /* available TSS */
	load_TR_desc();
}
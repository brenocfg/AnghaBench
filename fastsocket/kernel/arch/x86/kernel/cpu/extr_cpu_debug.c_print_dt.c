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
struct desc_ptr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_desc_ptr (char*,void*,struct desc_ptr) ; 
 int /*<<< orphan*/  seq_printf (void*,char*,unsigned long) ; 
 int /*<<< orphan*/  store_gdt (struct desc_ptr*) ; 
 int /*<<< orphan*/  store_idt (struct desc_ptr*) ; 
 int /*<<< orphan*/  store_ldt (unsigned long) ; 
 int /*<<< orphan*/  store_tr (unsigned long) ; 

__attribute__((used)) static void print_dt(void *seq)
{
	struct desc_ptr dt;
	unsigned long ldt;

	/* IDT */
	store_idt((struct desc_ptr *)&dt);
	print_desc_ptr("IDT", seq, dt);

	/* GDT */
	store_gdt((struct desc_ptr *)&dt);
	print_desc_ptr("GDT", seq, dt);

	/* LDT */
	store_ldt(ldt);
	seq_printf(seq, " LDT\t: %016lx\n", ldt);

	/* TR */
	store_tr(ldt);
	seq_printf(seq, " TR\t: %016lx\n", ldt);
}
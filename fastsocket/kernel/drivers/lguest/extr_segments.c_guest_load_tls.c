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
struct TYPE_2__ {struct desc_struct* gdt; } ;
struct lg_cpu {int /*<<< orphan*/  changed; TYPE_1__ arch; } ;
struct desc_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGED_GDT_TLS ; 
 int GDT_ENTRY_TLS_ENTRIES ; 
 scalar_t__ GDT_ENTRY_TLS_MAX ; 
 size_t GDT_ENTRY_TLS_MIN ; 
 int /*<<< orphan*/  __lgread (struct lg_cpu*,struct desc_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  fixup_gdt_table (struct lg_cpu*,size_t,scalar_t__) ; 

void guest_load_tls(struct lg_cpu *cpu, unsigned long gtls)
{
	struct desc_struct *tls = &cpu->arch.gdt[GDT_ENTRY_TLS_MIN];

	__lgread(cpu, tls, gtls, sizeof(*tls)*GDT_ENTRY_TLS_ENTRIES);
	fixup_gdt_table(cpu, GDT_ENTRY_TLS_MIN, GDT_ENTRY_TLS_MAX+1);
	/* Note that just the TLS entries have changed. */
	cpu->changed |= CHANGED_GDT_TLS;
}
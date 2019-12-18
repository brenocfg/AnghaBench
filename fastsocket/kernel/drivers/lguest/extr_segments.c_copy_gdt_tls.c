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
struct lg_cpu {TYPE_1__ arch; } ;
struct desc_struct {int dummy; } ;

/* Variables and functions */
 unsigned int GDT_ENTRY_TLS_MAX ; 
 unsigned int GDT_ENTRY_TLS_MIN ; 

void copy_gdt_tls(const struct lg_cpu *cpu, struct desc_struct *gdt)
{
	unsigned int i;

	for (i = GDT_ENTRY_TLS_MIN; i <= GDT_ENTRY_TLS_MAX; i++)
		gdt[i] = cpu->arch.gdt[i];
}
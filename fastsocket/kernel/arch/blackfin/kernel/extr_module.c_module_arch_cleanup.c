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
struct TYPE_2__ {int /*<<< orphan*/  bss_l2; int /*<<< orphan*/  data_l2; int /*<<< orphan*/  text_l2; int /*<<< orphan*/  bss_b_l1; int /*<<< orphan*/  data_b_l1; int /*<<< orphan*/  bss_a_l1; int /*<<< orphan*/  data_a_l1; int /*<<< orphan*/  text_l1; } ;
struct module {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  l1_data_A_sram_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l1_data_B_sram_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l1_inst_sram_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2_sram_free (int /*<<< orphan*/ ) ; 

void module_arch_cleanup(struct module *mod)
{
	l1_inst_sram_free(mod->arch.text_l1);
	l1_data_A_sram_free(mod->arch.data_a_l1);
	l1_data_A_sram_free(mod->arch.bss_a_l1);
	l1_data_B_sram_free(mod->arch.data_b_l1);
	l1_data_B_sram_free(mod->arch.bss_b_l1);
	l2_sram_free(mod->arch.text_l2);
	l2_sram_free(mod->arch.data_l2);
	l2_sram_free(mod->arch.bss_l2);
}
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
struct TYPE_2__ {int /*<<< orphan*/  e_phnum; } ;
typedef  int /*<<< orphan*/  Elf64_Half ;

/* Variables and functions */
 TYPE_1__* GATE_EHDR ; 

Elf64_Half elf_core_extra_phdrs(void)
{
	return GATE_EHDR->e_phnum;
}
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
typedef  int /*<<< orphan*/  Elf32_Sym ;
typedef  int /*<<< orphan*/  Elf32_Rel ;

/* Variables and functions */
 int reloc_count ; 

__attribute__((used)) static void count_reloc(Elf32_Rel *rel, Elf32_Sym *sym)
{
	reloc_count += 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  r_offset; } ;
typedef  int /*<<< orphan*/  Elf32_Sym ;
typedef  TYPE_1__ Elf32_Rel ;

/* Variables and functions */
 int /*<<< orphan*/  reloc_idx ; 
 int /*<<< orphan*/ * relocs ; 

__attribute__((used)) static void collect_reloc(Elf32_Rel *rel, Elf32_Sym *sym)
{
	/* Remember the address that needs to be adjusted. */
	relocs[reloc_idx++] = rel->r_offset;
}
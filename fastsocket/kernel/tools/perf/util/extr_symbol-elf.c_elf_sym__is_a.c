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
typedef  enum map_type { ____Placeholder_map_type } map_type ;
typedef  int /*<<< orphan*/  GElf_Sym ;

/* Variables and functions */
#define  MAP__FUNCTION 129 
#define  MAP__VARIABLE 128 
 int elf_sym__is_function (int /*<<< orphan*/ *) ; 
 int elf_sym__is_object (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool elf_sym__is_a(GElf_Sym *sym, enum map_type type)
{
	switch (type) {
	case MAP__FUNCTION:
		return elf_sym__is_function(sym);
	case MAP__VARIABLE:
		return elf_sym__is_object(sym);
	default:
		return false;
	}
}
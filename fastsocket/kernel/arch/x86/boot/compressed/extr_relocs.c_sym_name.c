#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sh_name; } ;
struct TYPE_7__ {TYPE_1__ shdr; } ;
struct TYPE_6__ {int st_name; size_t st_shndx; } ;
typedef  TYPE_2__ Elf32_Sym ;

/* Variables and functions */
 char* sec_name (int /*<<< orphan*/ ) ; 
 TYPE_4__* secs ; 

__attribute__((used)) static const char *sym_name(const char *sym_strtab, Elf32_Sym *sym)
{
	const char *name;
	name = "<noname>";
	if (sym->st_name) {
		name = sym_strtab + sym->st_name;
	}
	else {
		name = sec_name(secs[sym->st_shndx].shdr.sh_name);
	}
	return name;
}
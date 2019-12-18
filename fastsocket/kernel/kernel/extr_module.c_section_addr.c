#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ sh_addr; } ;
typedef  TYPE_1__ Elf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Ehdr ;

/* Variables and functions */
 size_t find_sec (int /*<<< orphan*/ *,TYPE_1__*,char const*,char const*) ; 

__attribute__((used)) static void *section_addr(Elf_Ehdr *hdr, Elf_Shdr *shdrs,
			  const char *secstrings, const char *name)
{
	/* Section 0 has sh_addr 0. */
	return (void *)shdrs[find_sec(hdr, shdrs, secstrings, name)].sh_addr;
}
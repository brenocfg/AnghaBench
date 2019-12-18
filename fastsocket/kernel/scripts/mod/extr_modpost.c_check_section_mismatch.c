#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct elf_info {int dummy; } ;
typedef  enum mismatch { ____Placeholder_mismatch } mismatch ;
struct TYPE_11__ {int /*<<< orphan*/  r_offset; int /*<<< orphan*/  r_addend; } ;
struct TYPE_10__ {int /*<<< orphan*/  st_shndx; } ;
typedef  TYPE_1__ Elf_Sym ;
typedef  TYPE_2__ Elf_Rela ;

/* Variables and functions */
 int NO_MISMATCH ; 
 TYPE_1__* find_elf_symbol (struct elf_info*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* find_elf_symbol2 (struct elf_info*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  is_function (TYPE_1__*) ; 
 int /*<<< orphan*/  report_sec_mismatch (char const*,int,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 
 char* sec_name (struct elf_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ secref_whitelist (char const*,char const*,char const*,char const*) ; 
 int section_mismatch (char const*,char const*) ; 
 char* sym_name (struct elf_info*,TYPE_1__*) ; 

__attribute__((used)) static void check_section_mismatch(const char *modname, struct elf_info *elf,
                                   Elf_Rela *r, Elf_Sym *sym, const char *fromsec)
{
	const char *tosec;
	enum mismatch mismatch;

	tosec = sec_name(elf, sym->st_shndx);
	mismatch = section_mismatch(fromsec, tosec);
	if (mismatch != NO_MISMATCH) {
		Elf_Sym *to;
		Elf_Sym *from;
		const char *tosym;
		const char *fromsym;

		from = find_elf_symbol2(elf, r->r_offset, fromsec);
		fromsym = sym_name(elf, from);
		to = find_elf_symbol(elf, r->r_addend, sym);
		tosym = sym_name(elf, to);

		/* check whitelist - we may ignore it */
		if (secref_whitelist(fromsec, fromsym, tosec, tosym)) {
			report_sec_mismatch(modname, mismatch,
			   fromsec, r->r_offset, fromsym,
			   is_function(from), tosec, tosym,
			   is_function(to));
		}
	}
}
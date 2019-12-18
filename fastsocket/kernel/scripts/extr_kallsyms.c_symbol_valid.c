#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sym_entry {scalar_t__* sym; scalar_t__ addr; } ;
struct TYPE_4__ {scalar_t__ end; char* etext; } ;
struct TYPE_3__ {scalar_t__ end; char* etext; } ;

/* Variables and functions */
 int /*<<< orphan*/  all_symbols ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 scalar_t__ symbol_prefix_char ; 
 scalar_t__ symbol_valid_tr (struct sym_entry*) ; 
 TYPE_2__* text_range_inittext ; 
 TYPE_1__* text_range_text ; 

__attribute__((used)) static int symbol_valid(struct sym_entry *s)
{
	/* Symbols which vary between passes.  Passes 1 and 2 must have
	 * identical symbol lists.  The kallsyms_* symbols below are only added
	 * after pass 1, they would be included in pass 2 when --all-symbols is
	 * specified so exclude them to get a stable symbol list.
	 */
	static char *special_symbols[] = {
		"kallsyms_addresses",
		"kallsyms_num_syms",
		"kallsyms_names",
		"kallsyms_markers",
		"kallsyms_token_table",
		"kallsyms_token_index",

	/* Exclude linker generated symbols which vary between passes */
		"_SDA_BASE_",		/* ppc */
		"_SDA2_BASE_",		/* ppc */
		NULL };
	int i;
	int offset = 1;

	/* skip prefix char */
	if (symbol_prefix_char && *(s->sym + 1) == symbol_prefix_char)
		offset++;

	/* if --all-symbols is not specified, then symbols outside the text
	 * and inittext sections are discarded */
	if (!all_symbols) {
		if (symbol_valid_tr(s) == 0)
			return 0;
		/* Corner case.  Discard any symbols with the same value as
		 * _etext _einittext; they can move between pass 1 and 2 when
		 * the kallsyms data are added.  If these symbols move then
		 * they may get dropped in pass 2, which breaks the kallsyms
		 * rules.
		 */
		if ((s->addr == text_range_text->end &&
				strcmp((char *)s->sym + offset, text_range_text->etext)) ||
		    (s->addr == text_range_inittext->end &&
				strcmp((char *)s->sym + offset, text_range_inittext->etext)))
			return 0;
	}

	/* Exclude symbols which vary between passes. */
	if (strstr((char *)s->sym + offset, "_compiled."))
		return 0;

	for (i = 0; special_symbols[i]; i++)
		if( strcmp((char *)s->sym + offset, special_symbols[i]) == 0 )
			return 0;

	return 1;
}
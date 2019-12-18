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
typedef  union etree_union {int dummy; } etree_union ;
typedef  int /*<<< orphan*/  reloc_howto_type ;
struct TYPE_3__ {char const* name; scalar_t__ output_offset; int /*<<< orphan*/ * output_section; scalar_t__ addend_value; union etree_union* addend_exp; int /*<<< orphan*/ * section; int /*<<< orphan*/ * howto; int /*<<< orphan*/  reloc; } ;
typedef  TYPE_1__ lang_reloc_statement_type ;
typedef  int /*<<< orphan*/  bfd_reloc_code_real_type ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  lang_reloc_statement ; 
 TYPE_1__* new_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_ptr ; 

void
lang_add_reloc (bfd_reloc_code_real_type reloc,
		reloc_howto_type *howto,
		asection *section,
		const char *name,
		union etree_union *addend)
{
  lang_reloc_statement_type *p = new_stat (lang_reloc_statement, stat_ptr);

  p->reloc = reloc;
  p->howto = howto;
  p->section = section;
  p->name = name;
  p->addend_exp = addend;

  p->addend_value = 0;
  p->output_section = NULL;
  p->output_offset = 0;
}
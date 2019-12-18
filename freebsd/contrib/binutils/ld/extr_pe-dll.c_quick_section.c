#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_9__ {scalar_t__ value; int /*<<< orphan*/  flags; TYPE_2__* section; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ asymbol ;
struct TYPE_10__ {int /*<<< orphan*/  name; struct TYPE_10__* output_section; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  BSF_LOCAL ; 
 int SEC_ALLOC ; 
 int SEC_KEEP ; 
 int SEC_LOAD ; 
 TYPE_1__* bfd_make_empty_symbol (int /*<<< orphan*/ *) ; 
 TYPE_2__* bfd_make_section_old_way (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  symptr ; 
 TYPE_1__** symtab ; 

__attribute__((used)) static asection *
quick_section (bfd *abfd, const char *name, int flags, int align)
{
  asection *sec;
  asymbol *sym;

  sec = bfd_make_section_old_way (abfd, name);
  bfd_set_section_flags (abfd, sec, flags | SEC_ALLOC | SEC_LOAD | SEC_KEEP);
  bfd_set_section_alignment (abfd, sec, align);
  /* Remember to undo this before trying to link internally!  */
  sec->output_section = sec;

  sym = bfd_make_empty_symbol (abfd);
  symtab[symptr++] = sym;
  sym->name = sec->name;
  sym->section = sec;
  sym->flags = BSF_LOCAL;
  sym->value = 0;

  return sec;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_5__ {int st_other; } ;
struct TYPE_6__ {TYPE_1__ internal_elf_sym; } ;
typedef  TYPE_2__ elf_symbol_type ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_asymbol_bfd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 TYPE_2__* elf_symbol_from (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_symbol_end () ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/ * symbol_find_or_make (char*) ; 
 int /*<<< orphan*/ * symbol_get_bfdsym (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
obj_elf_visibility (int visibility)
{
  char *name;
  int c;
  symbolS *symbolP;
  asymbol *bfdsym;
  elf_symbol_type *elfsym;

  do
    {
      name = input_line_pointer;
      c = get_symbol_end ();
      symbolP = symbol_find_or_make (name);
      *input_line_pointer = c;

      SKIP_WHITESPACE ();

      bfdsym = symbol_get_bfdsym (symbolP);
      elfsym = elf_symbol_from (bfd_asymbol_bfd (bfdsym), bfdsym);

      assert (elfsym);

      elfsym->internal_elf_sym.st_other &= ~3;
      elfsym->internal_elf_sym.st_other |= visibility;

      if (c == ',')
	{
	  input_line_pointer ++;

	  SKIP_WHITESPACE ();

	  if (*input_line_pointer == '\n')
	    c = '\n';
	}
    }
  while (c == ',');

  demand_empty_rest_of_line ();
}
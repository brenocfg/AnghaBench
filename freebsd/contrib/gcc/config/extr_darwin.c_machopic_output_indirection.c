#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {char* ptr_name; scalar_t__ stub_p; int /*<<< orphan*/  symbol; int /*<<< orphan*/  used; } ;
typedef  TYPE_1__ machopic_indirection ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE_ALIGNMENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 char* IDENTIFIER_POINTER (scalar_t__) ; 
 scalar_t__ IDENTIFIER_TRANSPARENT_ALIAS (scalar_t__) ; 
 int MACHO_SYMBOL_STATIC ; 
 int /*<<< orphan*/  Pmode ; 
 int SYMBOL_REF_FLAGS (int /*<<< orphan*/ ) ; 
 scalar_t__ SYMBOL_REF_LOCAL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 char* XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  assemble_align (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assemble_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assemble_label (char const*) ; 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/ * darwin_sections ; 
 int /*<<< orphan*/  data_section ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  indirect_data (int /*<<< orphan*/ ) ; 
 size_t machopic_nl_symbol_ptr_section ; 
 int /*<<< orphan*/  machopic_output_stub (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ machopic_symbol_defined_p (int /*<<< orphan*/ ) ; 
 scalar_t__ maybe_get_identifier (char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  switch_to_section (int /*<<< orphan*/ ) ; 
 char* user_label_prefix ; 

__attribute__((used)) static int
machopic_output_indirection (void **slot, void *data)
{
  machopic_indirection *p = *((machopic_indirection **) slot);
  FILE *asm_out_file = (FILE *) data;
  rtx symbol;
  const char *sym_name;
  const char *ptr_name;

  if (!p->used)
    return 1;

  symbol = p->symbol;
  sym_name = XSTR (symbol, 0);
  ptr_name = p->ptr_name;

  if (p->stub_p)
    {
      char *sym;
      char *stub;
      tree id;

      id = maybe_get_identifier (sym_name);
      if (id)
	{
	  tree id_orig = id;

	  while (IDENTIFIER_TRANSPARENT_ALIAS (id))
	    id = TREE_CHAIN (id);
	  if (id != id_orig)
	    sym_name = IDENTIFIER_POINTER (id);
	}

      sym = alloca (strlen (sym_name) + 2);
      if (sym_name[0] == '*' || sym_name[0] == '&')
	strcpy (sym, sym_name + 1);
      else if (sym_name[0] == '-' || sym_name[0] == '+')
	strcpy (sym, sym_name);
      else
	sprintf (sym, "%s%s", user_label_prefix, sym_name);

      stub = alloca (strlen (ptr_name) + 2);
      if (ptr_name[0] == '*' || ptr_name[0] == '&')
	strcpy (stub, ptr_name + 1);
      else
	sprintf (stub, "%s%s", user_label_prefix, ptr_name);

      machopic_output_stub (asm_out_file, sym, stub);
    }
  else if (! indirect_data (symbol)
	   && (machopic_symbol_defined_p (symbol)
	       || SYMBOL_REF_LOCAL_P (symbol)))
    {
      switch_to_section (data_section);
      assemble_align (GET_MODE_ALIGNMENT (Pmode));
      assemble_label (ptr_name);
      assemble_integer (gen_rtx_SYMBOL_REF (Pmode, sym_name),
			GET_MODE_SIZE (Pmode),
			GET_MODE_ALIGNMENT (Pmode), 1);
    }
  else
    {
      rtx init = const0_rtx;

      switch_to_section (darwin_sections[machopic_nl_symbol_ptr_section]);
      assemble_name (asm_out_file, ptr_name);
      fprintf (asm_out_file, ":\n");

      fprintf (asm_out_file, "\t.indirect_symbol ");
      assemble_name (asm_out_file, sym_name);
      fprintf (asm_out_file, "\n");

      /* Variables that are marked with MACHO_SYMBOL_STATIC need to
	 have their symbol name instead of 0 in the second entry of
	 the non-lazy symbol pointer data structure when they are
	 defined.  This allows the runtime to rebind newer instances
	 of the translation unit with the original instance of the
	 symbol.  */

      if ((SYMBOL_REF_FLAGS (symbol) & MACHO_SYMBOL_STATIC)
	  && machopic_symbol_defined_p (symbol))
	init = gen_rtx_SYMBOL_REF (Pmode, sym_name);

      assemble_integer (init, GET_MODE_SIZE (Pmode),
			GET_MODE_ALIGNMENT (Pmode), 1);
    }

  return 1;
}
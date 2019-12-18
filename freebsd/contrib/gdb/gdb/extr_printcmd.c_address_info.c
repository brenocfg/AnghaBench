#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;
typedef  struct symbol minimal_symbol ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ asection ;
struct TYPE_9__ {int /*<<< orphan*/  (* describe_location ) (struct symbol*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {scalar_t__ la_language; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_START (int /*<<< orphan*/ ) ; 
 char* DEPRECATED_SYMBOL_NAME (struct symbol*) ; 
 int /*<<< orphan*/  DMGL_ANSI ; 
#define  LOC_ARG 148 
#define  LOC_BASEREG 147 
#define  LOC_BASEREG_ARG 146 
#define  LOC_BLOCK 145 
#define  LOC_COMPUTED 144 
#define  LOC_COMPUTED_ARG 143 
#define  LOC_CONST 142 
#define  LOC_CONST_BYTES 141 
#define  LOC_HP_THREAD_LOCAL_STATIC 140 
#define  LOC_INDIRECT 139 
#define  LOC_LABEL 138 
#define  LOC_LOCAL 137 
#define  LOC_LOCAL_ARG 136 
#define  LOC_OPTIMIZED_OUT 135 
#define  LOC_REF_ARG 134 
#define  LOC_REGISTER 133 
#define  LOC_REGPARM 132 
#define  LOC_REGPARM_ADDR 131 
#define  LOC_STATIC 130 
#define  LOC_TYPEDEF 129 
#define  LOC_UNRESOLVED 128 
 int /*<<< orphan*/  REGISTER_NAME (long) ; 
 long SYMBOL_BASEREG (struct symbol*) ; 
 TYPE_1__* SYMBOL_BFD_SECTION (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_BLOCK_VALUE (struct symbol*) ; 
 int SYMBOL_CLASS (struct symbol*) ; 
 TYPE_5__* SYMBOL_OPS (struct symbol*) ; 
 long SYMBOL_VALUE (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct symbol*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 TYPE_4__* current_language ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fprintf_symbol_filtered (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  get_selected_block (int /*<<< orphan*/ ) ; 
 scalar_t__ language_objc ; 
 struct symbol* lookup_minimal_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct symbol* lookup_symbol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,struct symtab**) ; 
 int /*<<< orphan*/  overlay_unmapped_address (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  print_address_numeric (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 scalar_t__ section_is_overlay (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct symbol*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
address_info (char *exp, int from_tty)
{
  struct symbol *sym;
  struct minimal_symbol *msymbol;
  long val;
  long basereg;
  asection *section;
  CORE_ADDR load_addr;
  int is_a_field_of_this;	/* C++: lookup_symbol sets this to nonzero
				   if exp is a field of `this'. */

  if (exp == 0)
    error ("Argument required.");

  sym = lookup_symbol (exp, get_selected_block (0), VAR_DOMAIN,
		       &is_a_field_of_this, (struct symtab **) NULL);
  if (sym == NULL)
    {
      if (is_a_field_of_this)
	{
	  printf_filtered ("Symbol \"");
	  fprintf_symbol_filtered (gdb_stdout, exp,
				   current_language->la_language, DMGL_ANSI);
	  printf_filtered ("\" is a field of the local class variable ");
	  if (current_language->la_language == language_objc)
	    printf_filtered ("`self'\n");	/* ObjC equivalent of "this" */
	  else
	    printf_filtered ("`this'\n");
	  return;
	}

      msymbol = lookup_minimal_symbol (exp, NULL, NULL);

      if (msymbol != NULL)
	{
	  load_addr = SYMBOL_VALUE_ADDRESS (msymbol);

	  printf_filtered ("Symbol \"");
	  fprintf_symbol_filtered (gdb_stdout, exp,
				   current_language->la_language, DMGL_ANSI);
	  printf_filtered ("\" is at ");
	  print_address_numeric (load_addr, 1, gdb_stdout);
	  printf_filtered (" in a file compiled without debugging");
	  section = SYMBOL_BFD_SECTION (msymbol);
	  if (section_is_overlay (section))
	    {
	      load_addr = overlay_unmapped_address (load_addr, section);
	      printf_filtered (",\n -- loaded at ");
	      print_address_numeric (load_addr, 1, gdb_stdout);
	      printf_filtered (" in overlay section %s", section->name);
	    }
	  printf_filtered (".\n");
	}
      else
	error ("No symbol \"%s\" in current context.", exp);
      return;
    }

  printf_filtered ("Symbol \"");
  fprintf_symbol_filtered (gdb_stdout, DEPRECATED_SYMBOL_NAME (sym),
			   current_language->la_language, DMGL_ANSI);
  printf_filtered ("\" is ");
  val = SYMBOL_VALUE (sym);
  basereg = SYMBOL_BASEREG (sym);
  section = SYMBOL_BFD_SECTION (sym);

  switch (SYMBOL_CLASS (sym))
    {
    case LOC_CONST:
    case LOC_CONST_BYTES:
      printf_filtered ("constant");
      break;

    case LOC_LABEL:
      printf_filtered ("a label at address ");
      print_address_numeric (load_addr = SYMBOL_VALUE_ADDRESS (sym),
			     1, gdb_stdout);
      if (section_is_overlay (section))
	{
	  load_addr = overlay_unmapped_address (load_addr, section);
	  printf_filtered (",\n -- loaded at ");
	  print_address_numeric (load_addr, 1, gdb_stdout);
	  printf_filtered (" in overlay section %s", section->name);
	}
      break;

    case LOC_COMPUTED:
    case LOC_COMPUTED_ARG:
      /* FIXME: cagney/2004-01-26: It should be possible to
	 unconditionally call the SYMBOL_OPS method when available.
	 Unfortunately DWARF 2 stores the frame-base (instead of the
	 function) location in a function's symbol.  Oops!  For the
	 moment enable this when/where applicable.  */
      SYMBOL_OPS (sym)->describe_location (sym, gdb_stdout);
      break;

    case LOC_REGISTER:
      printf_filtered ("a variable in register %s", REGISTER_NAME (val));
      break;

    case LOC_STATIC:
      printf_filtered ("static storage at address ");
      print_address_numeric (load_addr = SYMBOL_VALUE_ADDRESS (sym),
			     1, gdb_stdout);
      if (section_is_overlay (section))
	{
	  load_addr = overlay_unmapped_address (load_addr, section);
	  printf_filtered (",\n -- loaded at ");
	  print_address_numeric (load_addr, 1, gdb_stdout);
	  printf_filtered (" in overlay section %s", section->name);
	}
      break;

    case LOC_INDIRECT:
      printf_filtered ("external global (indirect addressing), at address *(");
      print_address_numeric (load_addr = SYMBOL_VALUE_ADDRESS (sym),
			     1, gdb_stdout);
      printf_filtered (")");
      if (section_is_overlay (section))
	{
	  load_addr = overlay_unmapped_address (load_addr, section);
	  printf_filtered (",\n -- loaded at ");
	  print_address_numeric (load_addr, 1, gdb_stdout);
	  printf_filtered (" in overlay section %s", section->name);
	}
      break;

    case LOC_REGPARM:
      printf_filtered ("an argument in register %s", REGISTER_NAME (val));
      break;

    case LOC_REGPARM_ADDR:
      printf_filtered ("address of an argument in register %s", REGISTER_NAME (val));
      break;

    case LOC_ARG:
      printf_filtered ("an argument at offset %ld", val);
      break;

    case LOC_LOCAL_ARG:
      printf_filtered ("an argument at frame offset %ld", val);
      break;

    case LOC_LOCAL:
      printf_filtered ("a local variable at frame offset %ld", val);
      break;

    case LOC_REF_ARG:
      printf_filtered ("a reference argument at offset %ld", val);
      break;

    case LOC_BASEREG:
      printf_filtered ("a variable at offset %ld from register %s",
		       val, REGISTER_NAME (basereg));
      break;

    case LOC_BASEREG_ARG:
      printf_filtered ("an argument at offset %ld from register %s",
		       val, REGISTER_NAME (basereg));
      break;

    case LOC_TYPEDEF:
      printf_filtered ("a typedef");
      break;

    case LOC_BLOCK:
      printf_filtered ("a function at address ");
      print_address_numeric (load_addr = BLOCK_START (SYMBOL_BLOCK_VALUE (sym)),
			     1, gdb_stdout);
      if (section_is_overlay (section))
	{
	  load_addr = overlay_unmapped_address (load_addr, section);
	  printf_filtered (",\n -- loaded at ");
	  print_address_numeric (load_addr, 1, gdb_stdout);
	  printf_filtered (" in overlay section %s", section->name);
	}
      break;

    case LOC_UNRESOLVED:
      {
	struct minimal_symbol *msym;

	msym = lookup_minimal_symbol (DEPRECATED_SYMBOL_NAME (sym), NULL, NULL);
	if (msym == NULL)
	  printf_filtered ("unresolved");
	else
	  {
	    section = SYMBOL_BFD_SECTION (msym);
	    printf_filtered ("static storage at address ");
	    print_address_numeric (load_addr = SYMBOL_VALUE_ADDRESS (msym),
				   1, gdb_stdout);
	    if (section_is_overlay (section))
	      {
		load_addr = overlay_unmapped_address (load_addr, section);
		printf_filtered (",\n -- loaded at ");
		print_address_numeric (load_addr, 1, gdb_stdout);
		printf_filtered (" in overlay section %s", section->name);
	      }
	  }
      }
      break;

    case LOC_HP_THREAD_LOCAL_STATIC:
      printf_filtered (
			"a thread-local variable at offset %ld from the thread base register %s",
			val, REGISTER_NAME (basereg));
      break;

    case LOC_OPTIMIZED_OUT:
      printf_filtered ("optimized out");
      break;

    default:
      printf_filtered ("of unknown (botched) type");
      break;
    }
  printf_filtered (".\n");
}
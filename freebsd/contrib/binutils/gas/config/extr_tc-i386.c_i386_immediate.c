#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
typedef  TYPE_2__* segT ;
struct TYPE_16__ {scalar_t__ X_op; int X_add_number; int /*<<< orphan*/ * X_op_symbol; int /*<<< orphan*/ * X_add_symbol; } ;
typedef  TYPE_3__ expressionS ;
typedef  int addressT ;
struct TYPE_17__ {scalar_t__ imm_operands; int* types; int /*<<< orphan*/ * reloc; TYPE_1__* op; } ;
struct TYPE_15__ {char* name; } ;
struct TYPE_14__ {TYPE_3__* imms; } ;

/* Variables and functions */
 int Imm16 ; 
 int Imm32 ; 
 int Imm32S ; 
 int Imm64 ; 
 int Imm8 ; 
 scalar_t__ MAX_IMMEDIATE_OPERANDS ; 
 scalar_t__ OUTPUT_FLAVOR ; 
 scalar_t__ O_absent ; 
 scalar_t__ O_big ; 
 scalar_t__ O_constant ; 
 scalar_t__ O_register ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* absolute_section ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfd_is_com_section (TYPE_2__*) ; 
 scalar_t__ bfd_target_aout_flavour ; 
 TYPE_2__* bss_section ; 
 TYPE_2__* data_section ; 
 TYPE_2__* expression (TYPE_3__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_7__ i ; 
 TYPE_3__* im_expressions ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  intel_syntax ; 
 scalar_t__ is_space_char (char) ; 
 char* lex_got (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 
 TYPE_2__* text_section ; 
 size_t this_operand ; 
 TYPE_2__* undefined_section ; 
 int /*<<< orphan*/  use_rela_relocations ; 

__attribute__((used)) static int
i386_immediate (char *imm_start)
{
  char *save_input_line_pointer;
  char *gotfree_input_line;
  segT exp_seg = 0;
  expressionS *exp;
  unsigned int types = ~0U;

  if (i.imm_operands == MAX_IMMEDIATE_OPERANDS)
    {
      as_bad (_("at most %d immediate operands are allowed"),
	      MAX_IMMEDIATE_OPERANDS);
      return 0;
    }

  exp = &im_expressions[i.imm_operands++];
  i.op[this_operand].imms = exp;

  if (is_space_char (*imm_start))
    ++imm_start;

  save_input_line_pointer = input_line_pointer;
  input_line_pointer = imm_start;

  gotfree_input_line = lex_got (&i.reloc[this_operand], NULL, &types);
  if (gotfree_input_line)
    input_line_pointer = gotfree_input_line;

  exp_seg = expression (exp);

  SKIP_WHITESPACE ();
  if (*input_line_pointer)
    as_bad (_("junk `%s' after expression"), input_line_pointer);

  input_line_pointer = save_input_line_pointer;
  if (gotfree_input_line)
    free (gotfree_input_line);

  if (exp->X_op == O_absent || exp->X_op == O_big)
    {
      /* Missing or bad expr becomes absolute 0.  */
      as_bad (_("missing or invalid immediate expression `%s' taken as 0"),
	      imm_start);
      exp->X_op = O_constant;
      exp->X_add_number = 0;
      exp->X_add_symbol = (symbolS *) 0;
      exp->X_op_symbol = (symbolS *) 0;
    }
  else if (exp->X_op == O_constant)
    {
      /* Size it properly later.  */
      i.types[this_operand] |= Imm64;
      /* If BFD64, sign extend val.  */
      if (!use_rela_relocations
	  && (exp->X_add_number & ~(((addressT) 2 << 31) - 1)) == 0)
	exp->X_add_number
	  = (exp->X_add_number ^ ((addressT) 1 << 31)) - ((addressT) 1 << 31);
    }
#if (defined (OBJ_AOUT) || defined (OBJ_MAYBE_AOUT))
  else if (OUTPUT_FLAVOR == bfd_target_aout_flavour
	   && exp_seg != absolute_section
	   && exp_seg != text_section
	   && exp_seg != data_section
	   && exp_seg != bss_section
	   && exp_seg != undefined_section
	   && !bfd_is_com_section (exp_seg))
    {
      as_bad (_("unimplemented segment %s in operand"), exp_seg->name);
      return 0;
    }
#endif
  else if (!intel_syntax && exp->X_op == O_register)
    {
      as_bad (_("illegal immediate register operand %s"), imm_start);
      return 0;
    }
  else
    {
      /* This is an address.  The size of the address will be
	 determined later, depending on destination register,
	 suffix, or the default for the section.  */
      i.types[this_operand] |= Imm8 | Imm16 | Imm32 | Imm32S | Imm64;
      i.types[this_operand] &= types;
    }

  return 1;
}
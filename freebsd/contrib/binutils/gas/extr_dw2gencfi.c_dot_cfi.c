#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ offsetT ;
struct TYPE_6__ {TYPE_2__* frch_cfi_data; } ;
struct TYPE_5__ {TYPE_1__* cur_fde_data; scalar_t__ cur_cfa_offset; int /*<<< orphan*/  last_address; } ;
struct TYPE_4__ {int signal_frame; } ;

/* Variables and functions */
#define  CFI_adjust_cfa_offset 142 
#define  CFI_rel_offset 141 
#define  CFI_return_column 140 
#define  CFI_signal_frame 139 
#define  DW_CFA_GNU_window_save 138 
#define  DW_CFA_def_cfa 137 
#define  DW_CFA_def_cfa_offset 136 
#define  DW_CFA_def_cfa_register 135 
#define  DW_CFA_offset 134 
#define  DW_CFA_register 133 
#define  DW_CFA_remember_state 132 
#define  DW_CFA_restore 131 
#define  DW_CFA_restore_state 130 
#define  DW_CFA_same_value 129 
#define  DW_CFA_undefined 128 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 scalar_t__ S_GET_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfi_add_CFA_def_cfa (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  cfi_add_CFA_def_cfa_offset (scalar_t__) ; 
 int /*<<< orphan*/  cfi_add_CFA_def_cfa_register (unsigned int) ; 
 int /*<<< orphan*/  cfi_add_CFA_insn (int const) ; 
 int /*<<< orphan*/  cfi_add_CFA_offset (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  cfi_add_CFA_register (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  cfi_add_CFA_remember_state () ; 
 int /*<<< orphan*/  cfi_add_CFA_restore (unsigned int) ; 
 int /*<<< orphan*/  cfi_add_CFA_restore_state () ; 
 int /*<<< orphan*/  cfi_add_CFA_same_value (unsigned int) ; 
 int /*<<< orphan*/  cfi_add_CFA_undefined (unsigned int) ; 
 int /*<<< orphan*/  cfi_add_advance_loc (int /*<<< orphan*/ ) ; 
 scalar_t__ cfi_parse_const () ; 
 unsigned int cfi_parse_reg () ; 
 int /*<<< orphan*/  cfi_parse_separator () ; 
 int /*<<< orphan*/  cfi_set_return_column (unsigned int) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 scalar_t__ frag_now ; 
 scalar_t__ frag_now_fix () ; 
 TYPE_3__* frchain_now ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 scalar_t__ symbol_get_frag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_temp_new_now () ; 

__attribute__((used)) static void
dot_cfi (int arg)
{
  offsetT offset;
  unsigned reg1, reg2;

  if (frchain_now->frch_cfi_data == NULL)
    {
      as_bad (_("CFI instruction used without previous .cfi_startproc"));
      ignore_rest_of_line ();
      return;
    }

  /* If the last address was not at the current PC, advance to current.  */
  if (symbol_get_frag (frchain_now->frch_cfi_data->last_address) != frag_now
      || S_GET_VALUE (frchain_now->frch_cfi_data->last_address)
	 != frag_now_fix ())
    cfi_add_advance_loc (symbol_temp_new_now ());

  switch (arg)
    {
    case DW_CFA_offset:
      reg1 = cfi_parse_reg ();
      cfi_parse_separator ();
      offset = cfi_parse_const ();
      cfi_add_CFA_offset (reg1, offset);
      break;

    case CFI_rel_offset:
      reg1 = cfi_parse_reg ();
      cfi_parse_separator ();
      offset = cfi_parse_const ();
      cfi_add_CFA_offset (reg1,
			  offset - frchain_now->frch_cfi_data->cur_cfa_offset);
      break;

    case DW_CFA_def_cfa:
      reg1 = cfi_parse_reg ();
      cfi_parse_separator ();
      offset = cfi_parse_const ();
      cfi_add_CFA_def_cfa (reg1, offset);
      break;

    case DW_CFA_register:
      reg1 = cfi_parse_reg ();
      cfi_parse_separator ();
      reg2 = cfi_parse_reg ();
      cfi_add_CFA_register (reg1, reg2);
      break;

    case DW_CFA_def_cfa_register:
      reg1 = cfi_parse_reg ();
      cfi_add_CFA_def_cfa_register (reg1);
      break;

    case DW_CFA_def_cfa_offset:
      offset = cfi_parse_const ();
      cfi_add_CFA_def_cfa_offset (offset);
      break;

    case CFI_adjust_cfa_offset:
      offset = cfi_parse_const ();
      cfi_add_CFA_def_cfa_offset (frchain_now->frch_cfi_data->cur_cfa_offset
				  + offset);
      break;

    case DW_CFA_restore:
      for (;;)
	{
	  reg1 = cfi_parse_reg ();
	  cfi_add_CFA_restore (reg1);
	  SKIP_WHITESPACE ();
	  if (*input_line_pointer != ',')
	    break;
	  ++input_line_pointer;
	}
      break;

    case DW_CFA_undefined:
      for (;;)
	{
	  reg1 = cfi_parse_reg ();
	  cfi_add_CFA_undefined (reg1);
	  SKIP_WHITESPACE ();
	  if (*input_line_pointer != ',')
	    break;
	  ++input_line_pointer;
	}
      break;

    case DW_CFA_same_value:
      reg1 = cfi_parse_reg ();
      cfi_add_CFA_same_value (reg1);
      break;

    case CFI_return_column:
      reg1 = cfi_parse_reg ();
      cfi_set_return_column (reg1);
      break;

    case DW_CFA_remember_state:
      cfi_add_CFA_remember_state ();
      break;

    case DW_CFA_restore_state:
      cfi_add_CFA_restore_state ();
      break;

    case DW_CFA_GNU_window_save:
      cfi_add_CFA_insn (DW_CFA_GNU_window_save);
      break;

    case CFI_signal_frame:
      frchain_now->frch_cfi_data->cur_fde_data->signal_frame = 1;
      break;

    default:
      abort ();
    }

  demand_empty_rest_of_line ();
}
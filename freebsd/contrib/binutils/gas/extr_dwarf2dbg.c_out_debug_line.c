#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct line_seg {TYPE_1__* head; int /*<<< orphan*/  seg; struct line_seg* next; } ;
typedef  int /*<<< orphan*/  segT ;
struct TYPE_5__ {int X_add_number; int /*<<< orphan*/ * X_op_symbol; int /*<<< orphan*/ * X_add_symbol; void* X_op; } ;
typedef  TYPE_2__ expressionS ;
typedef  enum dwarf2_format { ____Placeholder_dwarf2_format } dwarf2_format ;
struct TYPE_4__ {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int DWARF2_FORMAT () ; 
 int DWARF2_LINE_BASE ; 
 int DWARF2_LINE_DEFAULT_IS_STMT ; 
 int DWARF2_LINE_MIN_INSN_LENGTH ; 
 int DWARF2_LINE_OPCODE_BASE ; 
 int DWARF2_LINE_RANGE ; 
 void* O_subtract ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct line_seg* all_segs ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ) ; 
 int dwarf2_format_32bit ; 
 int dwarf2_format_64bit ; 
 int dwarf2_format_64bit_irix ; 
 int /*<<< orphan*/  emit_expr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  out_byte (int) ; 
 int /*<<< orphan*/  out_file_list () ; 
 int /*<<< orphan*/  out_four (int) ; 
 int /*<<< orphan*/  out_two (int) ; 
 int /*<<< orphan*/  process_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subseg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_set_value_now (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_temp_make () ; 
 int /*<<< orphan*/ * symbol_temp_new_now () ; 

__attribute__((used)) static void
out_debug_line (segT line_seg)
{
  expressionS expr;
  symbolS *line_start;
  symbolS *prologue_end;
  symbolS *line_end;
  struct line_seg *s;
  enum dwarf2_format d2f;
  int sizeof_initial_length;
  int sizeof_offset;

  subseg_set (line_seg, 0);

  line_start = symbol_temp_new_now ();
  prologue_end = symbol_temp_make ();
  line_end = symbol_temp_make ();

  /* Total length of the information for this compilation unit.  */
  expr.X_op = O_subtract;
  expr.X_add_symbol = line_end;
  expr.X_op_symbol = line_start;

  d2f = DWARF2_FORMAT ();
  if (d2f == dwarf2_format_32bit)
    {
      sizeof_initial_length = sizeof_offset = 4;
    }
  else if (d2f == dwarf2_format_64bit)
    {
      sizeof_initial_length = 12;
      sizeof_offset = 8;
      out_four (-1);
    }
  else if (d2f == dwarf2_format_64bit_irix)
    {
      sizeof_initial_length = sizeof_offset = 8;
    }
  else
    {
      as_fatal (_("internal error: unknown dwarf2 format"));
    }
  expr.X_add_number = -sizeof_initial_length;
  emit_expr (&expr, sizeof_offset);

  /* Version.  */
  out_two (2);

  /* Length of the prologue following this length.  */
  expr.X_op = O_subtract;
  expr.X_add_symbol = prologue_end;
  expr.X_op_symbol = line_start;
  expr.X_add_number = - (sizeof_initial_length + 2 + sizeof_offset);
  emit_expr (&expr, sizeof_offset);

  /* Parameters of the state machine.  */
  out_byte (DWARF2_LINE_MIN_INSN_LENGTH);
  out_byte (DWARF2_LINE_DEFAULT_IS_STMT);
  out_byte (DWARF2_LINE_BASE);
  out_byte (DWARF2_LINE_RANGE);
  out_byte (DWARF2_LINE_OPCODE_BASE);

  /* Standard opcode lengths.  */
  out_byte (0);			/* DW_LNS_copy */
  out_byte (1);			/* DW_LNS_advance_pc */
  out_byte (1);			/* DW_LNS_advance_line */
  out_byte (1);			/* DW_LNS_set_file */
  out_byte (1);			/* DW_LNS_set_column */
  out_byte (0);			/* DW_LNS_negate_stmt */
  out_byte (0);			/* DW_LNS_set_basic_block */
  out_byte (0);			/* DW_LNS_const_add_pc */
  out_byte (1);			/* DW_LNS_fixed_advance_pc */
  out_byte (0);			/* DW_LNS_set_prologue_end */
  out_byte (0);			/* DW_LNS_set_epilogue_begin */
  out_byte (1);			/* DW_LNS_set_isa */

  out_file_list ();

  symbol_set_value_now (prologue_end);

  /* For each section, emit a statement program.  */
  for (s = all_segs; s; s = s->next)
    process_entries (s->seg, s->head->head);

  symbol_set_value_now (line_end);
}
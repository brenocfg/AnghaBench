#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
typedef  int /*<<< orphan*/  segT ;
struct TYPE_5__ {int X_add_number; int /*<<< orphan*/ * X_add_symbol; void* X_op; int /*<<< orphan*/ * X_op_symbol; } ;
typedef  TYPE_1__ expressionS ;
typedef  enum dwarf2_format { ____Placeholder_dwarf2_format } dwarf2_format ;
struct TYPE_7__ {int /*<<< orphan*/ * text_end; int /*<<< orphan*/ * text_start; int /*<<< orphan*/ * next; } ;
struct TYPE_6__ {int dir; char* filename; } ;

/* Variables and functions */
 int DWARF2_FORMAT () ; 
 int DW_LANG_Mips_Assembler ; 
 int /*<<< orphan*/  INSERT_DIR_SEPARATOR (char*,int) ; 
 void* O_subtract ; 
 void* O_symbol ; 
 int /*<<< orphan*/  TC_DWARF2_EMIT_OFFSET (int /*<<< orphan*/ ,int) ; 
 char* VERSION ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_4__* all_segs ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ) ; 
 char** dirs ; 
 int dwarf2_format_32bit ; 
 int dwarf2_format_64bit ; 
 int dwarf2_format_64bit_irix ; 
 int /*<<< orphan*/  emit_expr (TYPE_1__*,int) ; 
 TYPE_2__* files ; 
 int files_in_use ; 
 char* frag_more (int) ; 
 char* getpwd () ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  out_byte (int) ; 
 int /*<<< orphan*/  out_four (int) ; 
 int /*<<< orphan*/  out_two (int) ; 
 int /*<<< orphan*/  out_uleb128 (int) ; 
 int /*<<< orphan*/  section_symbol (int /*<<< orphan*/ ) ; 
 int sizeof_address ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  subseg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_set_value_now (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_temp_make () ; 
 int /*<<< orphan*/ * symbol_temp_new_now () ; 

__attribute__((used)) static void
out_debug_info (segT info_seg, segT abbrev_seg, segT line_seg, segT ranges_seg)
{
  char producer[128];
  char *comp_dir;
  expressionS expr;
  symbolS *info_start;
  symbolS *info_end;
  char *p;
  int len;
  enum dwarf2_format d2f;
  int sizeof_offset;

  subseg_set (info_seg, 0);

  info_start = symbol_temp_new_now ();
  info_end = symbol_temp_make ();

  /* Compilation Unit length.  */
  expr.X_op = O_subtract;
  expr.X_add_symbol = info_end;
  expr.X_op_symbol = info_start;

  d2f = DWARF2_FORMAT ();
  if (d2f == dwarf2_format_32bit)
    {
      expr.X_add_number = -4;
      emit_expr (&expr, 4);
      sizeof_offset = 4;
    }
  else if (d2f == dwarf2_format_64bit)
    {
      expr.X_add_number = -12;
      out_four (-1);
      emit_expr (&expr, 8);
      sizeof_offset = 8;
    }
  else if (d2f == dwarf2_format_64bit_irix)
    {
      expr.X_add_number = -8;
      emit_expr (&expr, 8);
      sizeof_offset = 8;
    }
  else
    {
      as_fatal (_("internal error: unknown dwarf2 format"));
    }

  /* DWARF version.  */
  out_two (2);

  /* .debug_abbrev offset */
  TC_DWARF2_EMIT_OFFSET (section_symbol (abbrev_seg), sizeof_offset);

  /* Target address size.  */
  out_byte (sizeof_address);

  /* DW_TAG_compile_unit DIE abbrev */
  out_uleb128 (1);

  /* DW_AT_stmt_list */
  /* ??? sizeof_offset */
  TC_DWARF2_EMIT_OFFSET (section_symbol (line_seg), 4);

  /* These two attributes are emitted if all of the code is contiguous.  */
  if (all_segs->next == NULL)
    {
      /* DW_AT_low_pc */
      expr.X_op = O_symbol;
      expr.X_add_symbol = all_segs->text_start;
      expr.X_add_number = 0;
      emit_expr (&expr, sizeof_address);

      /* DW_AT_high_pc */
      expr.X_op = O_symbol;
      expr.X_add_symbol = all_segs->text_end;
      expr.X_add_number = 0;
      emit_expr (&expr, sizeof_address);
    }
  else
    {
      /* This attribute is emitted if the code is disjoint.  */
      /* DW_AT_ranges.  */
      TC_DWARF2_EMIT_OFFSET (section_symbol (ranges_seg), sizeof_offset);
    }

  /* DW_AT_name.  We don't have the actual file name that was present
     on the command line, so assume files[1] is the main input file.
     We're not supposed to get called unless at least one line number
     entry was emitted, so this should always be defined.  */
  if (!files || files_in_use < 1)
    abort ();
  if (files[1].dir)
    {
      len = strlen (dirs[files[1].dir]);
      p = frag_more (len + 1);
      memcpy (p, dirs[files[1].dir], len);
      INSERT_DIR_SEPARATOR (p, len);
    }
  len = strlen (files[1].filename) + 1;
  p = frag_more (len);
  memcpy (p, files[1].filename, len);

  /* DW_AT_comp_dir */
  comp_dir = getpwd ();
  len = strlen (comp_dir) + 1;
  p = frag_more (len);
  memcpy (p, comp_dir, len);

  /* DW_AT_producer */
  sprintf (producer, "GNU AS %s", VERSION);
  len = strlen (producer) + 1;
  p = frag_more (len);
  memcpy (p, producer, len);

  /* DW_AT_language.  Yes, this is probably not really MIPS, but the
     dwarf2 draft has no standard code for assembler.  */
  out_two (DW_LANG_Mips_Assembler);

  symbol_set_value_now (info_end);
}
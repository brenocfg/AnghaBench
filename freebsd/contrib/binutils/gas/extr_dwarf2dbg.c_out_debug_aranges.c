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
typedef  int /*<<< orphan*/  symbolS ;
struct line_seg {int /*<<< orphan*/ * text_end; int /*<<< orphan*/  seg; int /*<<< orphan*/ * text_start; struct line_seg* next; } ;
typedef  int /*<<< orphan*/  segT ;
typedef  int /*<<< orphan*/  fragS ;
struct TYPE_3__ {scalar_t__ X_add_number; int /*<<< orphan*/ * X_op_symbol; int /*<<< orphan*/ * X_add_symbol; int /*<<< orphan*/  X_op; } ;
typedef  TYPE_1__ expressionS ;
typedef  int addressT ;

/* Variables and functions */
 int /*<<< orphan*/  O_subtract ; 
 int /*<<< orphan*/  O_symbol ; 
 int /*<<< orphan*/  TC_DWARF2_EMIT_OFFSET (int /*<<< orphan*/ ,int) ; 
 struct line_seg* all_segs ; 
 int /*<<< orphan*/  emit_expr (TYPE_1__*,unsigned int) ; 
 scalar_t__ ffs (int) ; 
 int /*<<< orphan*/ * first_frag_for_seg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag_align (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* frag_more (int) ; 
 int /*<<< orphan*/  get_frag_fix (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * last_frag_for_seg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_number_to_chars (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  out_byte (unsigned int) ; 
 int /*<<< orphan*/  out_four (int) ; 
 int /*<<< orphan*/  out_two (int) ; 
 int /*<<< orphan*/  section_symbol (int /*<<< orphan*/ ) ; 
 unsigned int sizeof_address ; 
 int /*<<< orphan*/  subseg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * symbol_temp_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
out_debug_aranges (segT aranges_seg, segT info_seg)
{
  unsigned int addr_size = sizeof_address;
  addressT size, skip;
  struct line_seg *s;
  expressionS expr;
  char *p;

  size = 4 + 2 + 4 + 1 + 1;

  skip = 2 * addr_size - (size & (2 * addr_size - 1));
  if (skip == 2 * addr_size)
    skip = 0;
  size += skip;

  for (s = all_segs; s; s = s->next)
    size += 2 * addr_size;

  size += 2 * addr_size;

  subseg_set (aranges_seg, 0);

  /* Length of the compilation unit.  */
  out_four (size - 4);

  /* Version.  */
  out_two (2);

  /* Offset to .debug_info.  */
  /* ??? sizeof_offset */
  TC_DWARF2_EMIT_OFFSET (section_symbol (info_seg), 4);

  /* Size of an address (offset portion).  */
  out_byte (addr_size);

  /* Size of a segment descriptor.  */
  out_byte (0);

  /* Align the header.  */
  if (skip)
    frag_align (ffs (2 * addr_size) - 1, 0, 0);

  for (s = all_segs; s; s = s->next)
    {
      fragS *frag;
      symbolS *beg, *end;

      frag = first_frag_for_seg (s->seg);
      beg = symbol_temp_new (s->seg, 0, frag);
      s->text_start = beg;

      frag = last_frag_for_seg (s->seg);
      end = symbol_temp_new (s->seg, get_frag_fix (frag, s->seg), frag);
      s->text_end = end;

      expr.X_op = O_symbol;
      expr.X_add_symbol = beg;
      expr.X_add_number = 0;
      emit_expr (&expr, addr_size);

      expr.X_op = O_subtract;
      expr.X_add_symbol = end;
      expr.X_op_symbol = beg;
      expr.X_add_number = 0;
      emit_expr (&expr, addr_size);
    }

  p = frag_more (2 * addr_size);
  md_number_to_chars (p, 0, addr_size);
  md_number_to_chars (p + addr_size, 0, addr_size);
}
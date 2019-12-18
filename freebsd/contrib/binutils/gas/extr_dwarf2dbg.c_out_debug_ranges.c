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
struct TYPE_3__ {scalar_t__ X_add_number; int /*<<< orphan*/ * X_add_symbol; void* X_op; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 void* O_symbol ; 
 struct line_seg* all_segs ; 
 int /*<<< orphan*/  emit_expr (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/ * first_frag_for_seg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_frag_fix (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * last_frag_for_seg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_byte (int) ; 
 unsigned int sizeof_address ; 
 int /*<<< orphan*/  subseg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * symbol_temp_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
out_debug_ranges (segT ranges_seg)
{
  unsigned int addr_size = sizeof_address;
  struct line_seg *s;
  expressionS expr;
  unsigned int i;

  subseg_set (ranges_seg, 0);

  /* Base Address Entry.  */
  for (i = 0; i < addr_size; i++) 
    out_byte (0xff);
  for (i = 0; i < addr_size; i++) 
    out_byte (0);

  /* Range List Entry.  */
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

      expr.X_op = O_symbol;
      expr.X_add_symbol = end;
      expr.X_add_number = 0;
      emit_expr (&expr, addr_size);
    }

  /* End of Range Entry.   */
  for (i = 0; i < addr_size; i++) 
    out_byte (0);
  for (i = 0; i < addr_size; i++) 
    out_byte (0);
}
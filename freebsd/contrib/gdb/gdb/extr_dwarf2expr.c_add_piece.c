#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dwarf_expr_piece {int in_reg; int /*<<< orphan*/  size; int /*<<< orphan*/  value; } ;
struct dwarf_expr_context {int num_pieces; struct dwarf_expr_piece* pieces; } ;
typedef  int /*<<< orphan*/  ULONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct dwarf_expr_piece* xmalloc (int) ; 
 struct dwarf_expr_piece* xrealloc (struct dwarf_expr_piece*,int) ; 

__attribute__((used)) static void
add_piece (struct dwarf_expr_context *ctx,
           int in_reg, CORE_ADDR value, ULONGEST size)
{
  struct dwarf_expr_piece *p;

  ctx->num_pieces++;

  if (ctx->pieces)
    ctx->pieces = xrealloc (ctx->pieces,
                            (ctx->num_pieces
                             * sizeof (struct dwarf_expr_piece)));
  else
    ctx->pieces = xmalloc (ctx->num_pieces
                           * sizeof (struct dwarf_expr_piece));

  p = &ctx->pieces[ctx->num_pieces - 1];
  p->in_reg = in_reg;
  p->value = value;
  p->size = size;
}
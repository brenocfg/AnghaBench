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
struct needs_frame_baton {scalar_t__ needs_frame; } ;
struct dwarf_expr_context {int in_reg; scalar_t__ num_pieces; TYPE_1__* pieces; int /*<<< orphan*/  get_tls_address; int /*<<< orphan*/  get_frame_base; int /*<<< orphan*/  read_mem; int /*<<< orphan*/  read_reg; struct needs_frame_baton* baton; } ;
struct TYPE_2__ {scalar_t__ in_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwarf_expr_eval (struct dwarf_expr_context*,unsigned char*,unsigned short) ; 
 int /*<<< orphan*/  free_dwarf_expr_context (struct dwarf_expr_context*) ; 
 int /*<<< orphan*/  needs_frame_frame_base ; 
 int /*<<< orphan*/  needs_frame_read_mem ; 
 int /*<<< orphan*/  needs_frame_read_reg ; 
 int /*<<< orphan*/  needs_frame_tls_address ; 
 struct dwarf_expr_context* new_dwarf_expr_context () ; 

__attribute__((used)) static int
dwarf2_loc_desc_needs_frame (unsigned char *data, unsigned short size)
{
  struct needs_frame_baton baton;
  struct dwarf_expr_context *ctx;
  int in_reg;

  baton.needs_frame = 0;

  ctx = new_dwarf_expr_context ();
  ctx->baton = &baton;
  ctx->read_reg = needs_frame_read_reg;
  ctx->read_mem = needs_frame_read_mem;
  ctx->get_frame_base = needs_frame_frame_base;
  ctx->get_tls_address = needs_frame_tls_address;

  dwarf_expr_eval (ctx, data, size);

  in_reg = ctx->in_reg;

  if (ctx->num_pieces > 0)
    {
      int i;

      /* If the location has several pieces, and any of them are in
         registers, then we will need a frame to fetch them from.  */
      for (i = 0; i < ctx->num_pieces; i++)
        if (ctx->pieces[i].in_reg)
          in_reg = 1;
    }

  free_dwarf_expr_context (ctx);

  return baton.needs_frame || in_reg;
}
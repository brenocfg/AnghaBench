#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ alloc; scalar_t__ size; int /*<<< orphan*/ * buf; } ;
struct TYPE_7__ {int flush; TYPE_1__* in_style; int /*<<< orphan*/  out_style; scalar_t__ style_start; scalar_t__ style_atom_count; TYPE_2__ style_atoms; } ;
typedef  TYPE_3__ hb_tx3g_style_context_t ;
struct TYPE_5__ {int /*<<< orphan*/  current; } ;

/* Variables and functions */

void hb_tx3g_style_reset(hb_tx3g_style_context_t * ctx)
{
    ctx->style_atoms.buf   = NULL;
    ctx->style_atoms.size  = 0;
    ctx->style_atoms.alloc = 0;
    ctx->style_atom_count  = 0;
    ctx->style_start       = 0;
    ctx->out_style         = ctx->in_style->current;
    ctx->flush             = 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; scalar_t__ fg_rgb; scalar_t__ fg_alpha; } ;
struct TYPE_7__ {int style_start; scalar_t__ flush; TYPE_3__ out_style; TYPE_1__* in_style; } ;
typedef  TYPE_2__ hb_tx3g_style_context_t ;
typedef  TYPE_3__ hb_subtitle_style_t ;
struct TYPE_6__ {TYPE_3__ current; } ;

/* Variables and functions */
 int TX3G_STYLES ; 
 int /*<<< orphan*/  tx3g_update_style_atoms (TYPE_2__*,int) ; 

__attribute__((used)) static int tx3g_update_style(hb_tx3g_style_context_t *ctx, int utf8_end_pos)
{
    hb_subtitle_style_t * style = &ctx->in_style->current;

    // do we need to add a style atom?
    if (((ctx->out_style.flags  ^ style->flags) & TX3G_STYLES) ||
          ctx->out_style.fg_rgb   != style->fg_rgb             ||
          ctx->out_style.fg_alpha != style->fg_alpha           ||
          ctx->flush)
    {
        if (ctx->style_start < utf8_end_pos)
        {
            if (!tx3g_update_style_atoms(ctx, utf8_end_pos - 1))
            {
                return 0;
            }
            ctx->style_start = utf8_end_pos;
        }
        ctx->out_style = *style;
        ctx->flush = 0;
    }

    return 1;
}
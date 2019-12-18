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
struct TYPE_4__ {int font_size; int fg_rgb; int alt_rgb; int ol_rgb; int bg_rgb; int fg_alpha; int alt_alpha; int ol_alpha; int bg_alpha; scalar_t__ flags; int /*<<< orphan*/  font_name; } ;
struct TYPE_5__ {scalar_t__ style_default; scalar_t__ styles_count; size_t event_style_default; TYPE_1__ current; TYPE_1__* styles; } ;
typedef  TYPE_2__ hb_subtitle_style_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_FONT_SANS ; 

__attribute__((used)) static void ssa_style_reset(hb_subtitle_style_context_t * ctx)
{
    if (ctx->styles != NULL && ctx->style_default < ctx->styles_count)
    {
        ctx->current = ctx->styles[ctx->event_style_default];
    }
    else
    {
        ctx->current.font_name = HB_FONT_SANS;
        ctx->current.font_size = 72;
        ctx->current.flags     = 0;
        ctx->current.fg_rgb    = 0x00FFFFFF;
        ctx->current.alt_rgb   = 0x00FFFFFF;
        ctx->current.ol_rgb    = 0x000F0F0F;
        ctx->current.bg_rgb    = 0x000F0F0F;

        ctx->current.fg_alpha  = 0xFF;
        ctx->current.alt_alpha = 0xFF;
        ctx->current.ol_alpha  = 0xFF;
        ctx->current.bg_alpha  = 0xFF;
    }
}
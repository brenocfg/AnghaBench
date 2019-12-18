#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int styles_count; struct TYPE_4__* styles; struct TYPE_4__* font_name; struct TYPE_4__* name; } ;
typedef  TYPE_1__ hb_subtitle_style_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void hb_subtitle_style_close(hb_subtitle_style_context_t ** pctx)
{
    if (pctx == NULL || *pctx == NULL)
    {
        return;
    }
    hb_subtitle_style_context_t * ctx = *pctx;

    if (ctx->styles != NULL)
    {
        int ii;

        for (ii = 0; ii < ctx->styles_count; ii++)
        {
            free(ctx->styles[ii].name);
            free(ctx->styles[ii].font_name);
        }
    }
    free(ctx->styles);
    free(ctx);
    *pctx = NULL;
}
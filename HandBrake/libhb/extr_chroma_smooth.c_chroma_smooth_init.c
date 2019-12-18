#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct hb_filter_private_s {int dummy; } ;
struct TYPE_12__ {TYPE_5__* plane_ctx; } ;
typedef  TYPE_2__ hb_filter_private_t ;
struct TYPE_13__ {int /*<<< orphan*/ * settings; TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_filter_object_t ;
struct TYPE_11__ {int /*<<< orphan*/  width; } ;
struct TYPE_14__ {TYPE_1__ geometry; } ;
typedef  TYPE_4__ hb_filter_init_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;
struct TYPE_15__ {int strength; int size; double amount; int steps; int scalebits; int halfscale; int /*<<< orphan*/  width; } ;
typedef  TYPE_5__ chroma_smooth_plane_context_t ;

/* Variables and functions */
 int CHROMA_SMOOTH_SIZE_DEFAULT ; 
 int CHROMA_SMOOTH_SIZE_MAX ; 
 int CHROMA_SMOOTH_SIZE_MIN ; 
 int CHROMA_SMOOTH_STRENGTH_DEFAULT ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  chroma_smooth_close (TYPE_3__*) ; 
 scalar_t__ chroma_smooth_init_thread (TYPE_3__*,int) ; 
 int /*<<< orphan*/  hb_dict_extract_double (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_extract_int (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_error (char*) ; 

__attribute__((used)) static int chroma_smooth_init(hb_filter_object_t *filter,
                              hb_filter_init_t   *init)
{
    filter->private_data = calloc(sizeof(struct hb_filter_private_s), 1);
    if (filter->private_data == NULL)
    {
        hb_error("Chroma Smooth calloc failed");
        return -1;
    }
    hb_filter_private_t * pv = filter->private_data;

    // Mark parameters unset
    for (int c = 0; c < 3; c++)
    {
        pv->plane_ctx[c].strength = -1;
        pv->plane_ctx[c].size     = -1;
    }

    // Read user parameters
    if (filter->settings != NULL)
    {
        hb_dict_t * dict = filter->settings;
        hb_dict_extract_double(&pv->plane_ctx[1].strength, dict, "cb-strength");
        hb_dict_extract_int(&pv->plane_ctx[1].size,        dict, "cb-size");

        hb_dict_extract_double(&pv->plane_ctx[2].strength, dict, "cr-strength");
        hb_dict_extract_int(&pv->plane_ctx[2].size,        dict, "cr-size");
    }

    // Cascade values
    // Cr not set; inherit Cb. Cb not set; defaults.
    for (int c = 2; c < 3; c++)
    {
        chroma_smooth_plane_context_t * prev_ctx = &pv->plane_ctx[c - 1];
        chroma_smooth_plane_context_t * ctx      = &pv->plane_ctx[c];

        if (ctx->strength == -1) ctx->strength = prev_ctx->strength;
        if (ctx->size     == -1) ctx->size     = prev_ctx->size;
    }

    for (int c = 0; c < 3; c++)
    {
        chroma_smooth_plane_context_t * ctx = &pv->plane_ctx[c];

        ctx->width = init->geometry.width;

        // Replace unset values with defaults
        if (ctx->strength == -1)
        {
            ctx->strength = CHROMA_SMOOTH_STRENGTH_DEFAULT;
        }
        if (ctx->size     == -1)
        {
            ctx->size     = CHROMA_SMOOTH_SIZE_DEFAULT;
        }

        // Sanitize
        if (ctx->strength < 0) ctx->strength = 0;
        if (ctx->strength > 3) ctx->strength = 3;
        if (ctx->size % 2 == 0) ctx->size--;
        if (ctx->size < CHROMA_SMOOTH_SIZE_MIN) ctx->size = CHROMA_SMOOTH_SIZE_MIN;
        if (ctx->size > CHROMA_SMOOTH_SIZE_MAX) ctx->size = CHROMA_SMOOTH_SIZE_MAX;

        if (c)
        {
            // Chroma
            ctx->amount    = ctx->strength * 65536.0;
            ctx->steps     = ctx->size / 2;
            ctx->scalebits = ctx->steps * 4;
            ctx->halfscale = 1 << (ctx->scalebits - 1);
        }
        else
        {
            // Luma
            ctx->amount    = 0;
            ctx->steps     = 0;
            ctx->scalebits = 0;
            ctx->halfscale = 0;
        }
    }

    if (chroma_smooth_init_thread(filter, 1) < 0)
    {
        chroma_smooth_close(filter);
        return -1;
    }

    return 0;
}
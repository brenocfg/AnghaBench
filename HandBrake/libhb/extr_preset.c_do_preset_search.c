#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int depth; } ;
struct TYPE_5__ {TYPE_1__ path; } ;
struct TYPE_6__ {int last_match_idx; int /*<<< orphan*/  type; int /*<<< orphan*/  name; scalar_t__ recurse; TYPE_2__ do_ctx; } ;
typedef  TYPE_3__ preset_search_context_t ;
typedef  int /*<<< orphan*/  preset_do_context_t ;
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int PRESET_DO_NEXT ; 
 int PRESET_DO_PARTIAL ; 
 int PRESET_DO_SKIP ; 
 int preset_cmp_idx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_preset_search(hb_value_t *preset, preset_do_context_t *do_ctx)
{
    preset_search_context_t *ctx = (preset_search_context_t*)do_ctx;
    int idx, result;

    idx = ctx->do_ctx.path.depth - 1;
    if (ctx->last_match_idx >= 0 && idx > ctx->last_match_idx)
    {
        // If there was a previous partial match, try to continue the match
        idx -= ctx->last_match_idx;
    }

    result = preset_cmp_idx(preset, idx, ctx->name, ctx->type);
    if (ctx->recurse && result == PRESET_DO_SKIP)
    {
        result = preset_cmp_idx(preset, 0, ctx->name, ctx->type);
        ctx->last_match_idx = idx;
    }
    if (result == PRESET_DO_PARTIAL)
    {
        return PRESET_DO_NEXT;
    }
    else
    {
        ctx->last_match_idx = -1;
    }

    return result;
}
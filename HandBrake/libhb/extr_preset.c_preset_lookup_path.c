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
struct TYPE_6__ {int depth; } ;
struct TYPE_4__ {TYPE_3__ path; } ;
struct TYPE_5__ {char const* name; int type; int recurse; int last_match_idx; TYPE_1__ do_ctx; } ;
typedef  TYPE_2__ preset_search_context_t ;
typedef  int /*<<< orphan*/  preset_do_context_t ;
typedef  int /*<<< orphan*/  hb_preset_index_t ;

/* Variables and functions */
 int PRESET_DO_SUCCESS ; 
 int /*<<< orphan*/  do_preset_search ; 
 int /*<<< orphan*/ * hb_preset_index_dup (TYPE_3__*) ; 
 int /*<<< orphan*/  hb_presets ; 
 int presets_do (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static hb_preset_index_t * preset_lookup_path(const char *name,
                                              int recurse, int type)
{
    preset_search_context_t ctx;
    int result;

    ctx.do_ctx.path.depth = 1;
    ctx.name = name;
    ctx.type = type;
    ctx.recurse = recurse;
    ctx.last_match_idx = -1;
    result = presets_do(do_preset_search, hb_presets,
                        (preset_do_context_t*)&ctx);
    if (result != PRESET_DO_SUCCESS)
        ctx.do_ctx.path.depth = 0;

    return hb_preset_index_dup(&ctx.do_ctx.path);
}
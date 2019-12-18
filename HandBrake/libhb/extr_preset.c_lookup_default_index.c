#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int depth; } ;
struct TYPE_4__ {TYPE_3__ path; } ;
typedef  TYPE_1__ preset_do_context_t ;
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  int /*<<< orphan*/  hb_preset_index_t ;

/* Variables and functions */
 int PRESET_DO_SUCCESS ; 
 int /*<<< orphan*/  do_find_default ; 
 int /*<<< orphan*/ * hb_preset_index_dup (TYPE_3__*) ; 
 int presets_do (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static hb_preset_index_t * lookup_default_index(hb_value_t *list)
{
    preset_do_context_t ctx;
    int result;

    ctx.path.depth = 1;
    result = presets_do(do_find_default, list, &ctx);
    if (result != PRESET_DO_SUCCESS)
        ctx.path.depth = 0;
    return hb_preset_index_dup(&ctx.path);
}
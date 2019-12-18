#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int depth; } ;
struct TYPE_8__ {TYPE_1__ path; } ;
typedef  TYPE_2__ preset_do_context_t ;
typedef  int /*<<< orphan*/  hb_value_t ;
struct TYPE_9__ {scalar_t__ depth; } ;
typedef  TYPE_3__ hb_preset_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_clear_default ; 
 int /*<<< orphan*/  do_delete_builtin ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/ * hb_presets ; 
 int /*<<< orphan*/  hb_presets_builtin ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_value_array_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_value_incref (int /*<<< orphan*/ *) ; 
 TYPE_3__* lookup_default_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  presets_do (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 

void hb_presets_builtin_update(void)
{
    preset_do_context_t ctx;
    hb_preset_index_t *path;
    hb_value_t *builtin;
    int ii;

    ctx.path.depth = 1;
    presets_do(do_delete_builtin, hb_presets, &ctx);

    builtin = hb_value_dup(hb_presets_builtin);
    path = lookup_default_index(hb_presets);
    if (path != NULL && path->depth != 0)
    {
        // The "Default" preset is an existing custom preset.
        // Clear the default preset in builtins
        ctx.path.depth = 1;
        presets_do(do_clear_default, builtin, &ctx);
    }
    free(path);

    for (ii = hb_value_array_len(builtin) - 1; ii >= 0; ii--)
    {
        hb_value_t *dict;
        dict = hb_value_array_get(builtin, ii);
        hb_value_incref(dict);
        hb_value_array_insert(hb_presets, 0, dict);
    }
    hb_value_free(&builtin);
}
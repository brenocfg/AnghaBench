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
struct TYPE_6__ {int result; int /*<<< orphan*/  micro; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; TYPE_2__ do_ctx; } ;
typedef  TYPE_3__ preset_import_context_t ;
typedef  int /*<<< orphan*/  preset_do_context_t ;
typedef  int /*<<< orphan*/  const hb_value_t ;

/* Variables and functions */
 scalar_t__ cmpVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_preset_import ; 
 int /*<<< orphan*/  const* hb_presets_update_version (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hb_presets_version (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* hb_value_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  const* import_hierarchy_29_0_0 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  presets_do (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int hb_presets_import(const hb_value_t *in, hb_value_t **out)
{
    preset_import_context_t   ctx;
    hb_value_t              * dup;

    ctx.do_ctx.path.depth = 1;
    ctx.result = 0;

    // Done modify the input
    dup = hb_value_dup(in);
    hb_presets_version(dup, &ctx.major, &ctx.minor, &ctx.micro);
    presets_do(do_preset_import, dup, (preset_do_context_t*)&ctx);
    if (cmpVersion(ctx.major, ctx.minor, ctx.micro, 29, 0, 0) <= 0)
    {
        hb_value_t * tmp;

        tmp  = import_hierarchy_29_0_0(dup);
        *out = hb_presets_update_version(tmp);
        hb_value_free(&tmp);
    }
    else if (ctx.result)
    {
        *out = hb_presets_update_version(dup);
    }
    else
    {
        *out = hb_value_dup(dup);
    }
    hb_value_free(&dup);

    return ctx.result;
}
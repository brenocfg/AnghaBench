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
typedef  int /*<<< orphan*/  preset_do_context_t ;
struct TYPE_4__ {int depth; } ;
struct TYPE_5__ {TYPE_1__ path; } ;
struct TYPE_6__ {int /*<<< orphan*/ * template; TYPE_2__ do_ctx; } ;
typedef  TYPE_3__ preset_clean_context_t ;
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_preset_clean ; 
 int /*<<< orphan*/  presets_do (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void presets_clean(hb_value_t *presets, hb_value_t *template)
{
    preset_clean_context_t ctx;
    ctx.do_ctx.path.depth = 1;
    ctx.template = template;
    presets_do(do_preset_clean, presets, (preset_do_context_t*)&ctx);
}
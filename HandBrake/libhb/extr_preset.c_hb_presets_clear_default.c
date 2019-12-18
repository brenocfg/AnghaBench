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
struct TYPE_4__ {int depth; } ;
struct TYPE_5__ {TYPE_1__ path; } ;
typedef  TYPE_2__ preset_do_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_clear_default ; 
 int /*<<< orphan*/  hb_presets ; 
 int /*<<< orphan*/  presets_do (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

void hb_presets_clear_default()
{
    preset_do_context_t ctx;
    ctx.path.depth = 1;
    presets_do(do_clear_default, hb_presets, &ctx);
}
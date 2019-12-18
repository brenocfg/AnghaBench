#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  preset_do_context_t ;
struct TYPE_2__ {int /*<<< orphan*/  template; } ;
typedef  TYPE_1__ preset_clean_context_t ;
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int PRESET_DO_NEXT ; 
 int /*<<< orphan*/  preset_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_preset_clean(hb_value_t *preset, preset_do_context_t *do_ctx)
{
    preset_clean_context_t *ctx = (preset_clean_context_t*)do_ctx;
    preset_clean(preset, ctx->template);
    return PRESET_DO_NEXT;
}
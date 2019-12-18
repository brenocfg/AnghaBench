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
struct TYPE_2__ {int /*<<< orphan*/  micro; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ preset_import_context_t ;
typedef  int /*<<< orphan*/  preset_do_context_t ;
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int PRESET_DO_NEXT ; 
 int /*<<< orphan*/  preset_import (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_preset_import(hb_value_t *preset, preset_do_context_t *do_ctx)
{
    preset_import_context_t *ctx = (preset_import_context_t*)do_ctx;
    ctx->result |= preset_import(preset, ctx->major, ctx->minor, ctx->micro);
    return PRESET_DO_NEXT;
}
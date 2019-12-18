#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  preset_do_context_t ;
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int PRESET_DO_NEXT ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_bool (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_clear_default(hb_value_t *preset, preset_do_context_t *ctx)
{
    hb_dict_set(preset, "Default", hb_value_bool(0));
    return PRESET_DO_NEXT;
}
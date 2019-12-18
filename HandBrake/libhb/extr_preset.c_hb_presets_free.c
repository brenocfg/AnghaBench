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

/* Variables and functions */
 int /*<<< orphan*/  hb_preset_template ; 
 int /*<<< orphan*/  hb_presets ; 
 int /*<<< orphan*/  hb_presets_builtin ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ *) ; 

void hb_presets_free(void)
{
    hb_value_free(&hb_preset_template);
    hb_value_free(&hb_presets);
    hb_value_free(&hb_presets_builtin);
}
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
typedef  int /*<<< orphan*/  hb_preset_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_presets ; 
 int /*<<< orphan*/ * lookup_default_index (int /*<<< orphan*/ ) ; 

hb_preset_index_t * hb_presets_get_default_index(void)
{
    hb_preset_index_t *path = lookup_default_index(hb_presets);
    return path;
}
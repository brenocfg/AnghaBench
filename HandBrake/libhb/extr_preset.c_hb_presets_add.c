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
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int hb_presets_add_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * presets_unpackage (int /*<<< orphan*/ *) ; 

int hb_presets_add(hb_value_t *preset)
{
    if (preset == NULL)
        return -1;

    preset = presets_unpackage(preset);
    if (preset == NULL)
        return -1;

    return hb_presets_add_internal(preset);
}
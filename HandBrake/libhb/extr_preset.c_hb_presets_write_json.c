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
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int hb_value_write_json (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * presets_package (int /*<<< orphan*/  const*) ; 

int hb_presets_write_json(const hb_value_t *preset, const char *path)
{
    hb_value_t *packaged_preset = presets_package(preset);
    // Packaging does some validity checks and can fail
    if (packaged_preset == NULL)
        return -1;
    int result = hb_value_write_json(packaged_preset, path);
    hb_value_free(&packaged_preset);
    return result;
}
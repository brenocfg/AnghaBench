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
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_make_custom ; 
 int /*<<< orphan*/ * hb_plist_parse_file (char const*) ; 
 int hb_presets_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * hb_value_read_json (char const*) ; 
 int /*<<< orphan*/  presets_do (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 

int hb_presets_add_file(const char *filename)
{
    hb_value_t *preset = hb_value_read_json(filename);
    if (preset == NULL)
        preset = hb_plist_parse_file(filename);
    if (preset == NULL)
        return -1;

    preset_do_context_t ctx;

    ctx.path.depth = 1;
    presets_do(do_make_custom, preset, &ctx);

    int result = hb_presets_add(preset);
    hb_value_free(&preset);

    return result;
}
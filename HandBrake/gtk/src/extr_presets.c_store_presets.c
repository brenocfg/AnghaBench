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
typedef  int /*<<< orphan*/  gchar ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_get_user_config_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_presets_get () ; 
 int /*<<< orphan*/  hb_presets_write_json (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
store_presets()
{
    gchar      *config, *path;
    hb_value_t *presets;

    config  = ghb_get_user_config_dir(NULL);
    path    = g_strdup_printf ("%s/%s", config, "presets.json");
    presets = hb_presets_get();
    hb_presets_write_json(presets, path);
    g_free(config);
    g_free(path);
}
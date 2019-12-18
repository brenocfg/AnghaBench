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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ghb_get_user_config_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_json_write_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
write_config_file(const gchar *name, GhbValue *dict)
{
    gchar *config, *path;

    config = ghb_get_user_config_dir(NULL);
    path   = g_strdup_printf ("%s/%s", config, name);
    g_free(config);
    ghb_json_write_file(path, dict);
    g_free(path);
}
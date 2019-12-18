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
 int /*<<< orphan*/  G_FILE_TEST_IS_REGULAR ; 
 scalar_t__ g_file_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ghb_get_user_config_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_json_parse_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_plist_parse_file (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GhbValue*
read_config_file(const gchar *name)
{
    gchar    *config, *path;
    GhbValue *gval = NULL;

    config = ghb_get_user_config_dir(NULL);
    path   = g_strdup_printf ("%s/%s", config, name);
    g_free(config);
    if (g_file_test(path, G_FILE_TEST_IS_REGULAR))
    {
        gval = ghb_json_parse_file(path);
        if (gval == NULL)
            gval = hb_plist_parse_file(path);
    }
    g_free(path);
    return gval;
}
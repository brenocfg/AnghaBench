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
typedef  size_t gint ;
typedef  char const gchar ;

/* Variables and functions */
 int /*<<< orphan*/  G_DIR_SEPARATOR_S ; 
 int /*<<< orphan*/  G_FILE_TEST_IS_DIR ; 
 int /*<<< orphan*/  g_file_test (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char const*) ; 
 char* g_get_home_dir () ; 
 char* g_get_user_config_dir () ; 
 int /*<<< orphan*/  g_mkdir (char const*,int) ; 
 char* g_strdup_printf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  g_strfreev (char const**) ; 
 char** g_strsplit (char const*,int /*<<< orphan*/ ,int) ; 
 char* override_user_config_dir ; 

gchar *
ghb_get_user_config_dir(gchar *subdir)
{
    const gchar * dir, * ghb = "ghb";
    gchar       * config;

    if (override_user_config_dir != NULL)
    {
        dir = override_user_config_dir;
    }
    else
    {
        dir = g_get_user_config_dir();
    }
    if (dir == NULL || !g_file_test(dir, G_FILE_TEST_IS_DIR))
    {
        dir = g_get_home_dir();
        ghb = ".ghb";
    }
    if (dir == NULL || !g_file_test(dir, G_FILE_TEST_IS_DIR))
    {
        // Last ditch, use CWD
        dir = "./";
        ghb = ".ghb";
    }
    config = g_strdup_printf("%s/%s", dir, ghb);
    if (!g_file_test(config, G_FILE_TEST_IS_DIR))
        g_mkdir (config, 0755);
    if (subdir)
    {
        gchar **split;
        gint    ii;

        split = g_strsplit(subdir, G_DIR_SEPARATOR_S, -1);
        for (ii = 0; split[ii] != NULL; ii++)
        {
            gchar *tmp;

            tmp = g_strdup_printf ("%s/%s", config, split[ii]);
            g_free(config);
            config = tmp;
            if (!g_file_test(config, G_FILE_TEST_IS_DIR))
                g_mkdir (config, 0755);
        }
        g_strfreev(split);
    }
    return config;
}
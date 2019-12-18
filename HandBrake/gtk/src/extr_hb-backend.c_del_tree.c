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
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GDir ;

/* Variables and functions */
 int /*<<< orphan*/  G_FILE_TEST_IS_DIR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  g_dir_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_open (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_read_name (int /*<<< orphan*/ *) ; 
 scalar_t__ g_file_test (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_rmdir (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  g_unlink (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
del_tree(const gchar *name, gboolean del_top)
{
    const gchar *file;

    if (g_file_test(name, G_FILE_TEST_IS_DIR))
    {
        GDir *gdir = g_dir_open(name, 0, NULL);
        file = g_dir_read_name(gdir);
        while (file)
        {
            gchar *path;
            path = g_strdup_printf("%s/%s", name, file);
            del_tree(path, TRUE);
            g_free(path);
            file = g_dir_read_name(gdir);
        }
        if (del_top)
            g_rmdir(name);
        g_dir_close(gdir);
    }
    else
    {
        g_unlink(name);
    }
}
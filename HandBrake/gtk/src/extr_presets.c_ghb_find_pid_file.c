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
typedef  int /*<<< orphan*/  GDir ;

/* Variables and functions */
 int /*<<< orphan*/  F_TLOCK ; 
 int /*<<< orphan*/  G_FILE_TEST_IS_DIR ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  g_dir_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_read_name (int /*<<< orphan*/ *) ; 
 scalar_t__ g_file_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  g_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_get_user_config_dir (int /*<<< orphan*/ *) ; 
 int lockf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/  const*,char*,int*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/  const*,char*,int) ; 

int
ghb_find_pid_file()
{
    const gchar *file;
    gchar       *config;

    config = ghb_get_user_config_dir(NULL);

    if (g_file_test(config, G_FILE_TEST_IS_DIR))
    {
        GDir *gdir;
        gdir = g_dir_open(config, 0, NULL);
        file = g_dir_read_name(gdir);
        while (file)
        {
            if (strncmp(file, "ghb.pid.", 8) == 0)
            {
                gchar *path;
                int    pid;

                sscanf(file, "ghb.pid.%d", &pid);
                path = g_strdup_printf("%s/%s", config, file);

#if !defined(_WIN32)
                int fd, lock = 1;

                fd = open(path, O_RDWR);
                if (fd >= 0)
                {
                    lock = lockf(fd, F_TLOCK, 0);
                }
                if (lock == 0)
                {
                    close(fd);
                    g_dir_close(gdir);
                    g_unlink(path);
                    g_free(path);
                    g_free(config);
                    return pid;
                }
                g_free(path);
                close(fd);
#else
                g_dir_close(gdir);
                g_unlink(path);
                g_free(path);
                g_free(config);
                return pid;
#endif
            }
            file = g_dir_read_name(gdir);
        }
        g_dir_close(gdir);
    }
    g_free(config);
    return -1;
}
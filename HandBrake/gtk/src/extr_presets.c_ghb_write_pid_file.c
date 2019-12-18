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
typedef  int pid_t ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  F_TLOCK ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * g_fopen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ *,int) ; 
 int getpid () ; 
 int /*<<< orphan*/ * ghb_get_user_config_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ *,int,int) ; 

void
ghb_write_pid_file()
{
#if !defined(_WIN32)
    gchar *config, *path;
    pid_t  pid;
    FILE  *fp;
    int    fd;

    pid    = getpid();
    config = ghb_get_user_config_dir(NULL);
    path   = g_strdup_printf ("%s/ghb.pid.%d", config, pid);
    fp     = g_fopen(path, "w");

    if (fp != NULL)
    {
        fprintf(fp, "%d\n", pid);
        fclose(fp);
    }

    fd = open(path, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
    if (fd >= 0)
    {
        lockf(fd, F_TLOCK, 0);
    }

    g_free(config);
    g_free(path);
#endif
}
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
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  G_FILE_ERROR ; 
 int /*<<< orphan*/  G_STRLOC ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  g_file_error_from_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ write (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int chassis_frontend_write_pidfile(const char *pid_file, GError **gerr) {
	int fd;
	int ret = 0;

	gchar *pid_str;

	/**
	 * write the PID file
	 */

	if (-1 == (fd = open(pid_file, O_WRONLY|O_TRUNC|O_CREAT, 0600))) {
		g_set_error(gerr,
				G_FILE_ERROR,
				g_file_error_from_errno(errno),
				"%s: open(%s) failed: %s", 
				G_STRLOC,
				pid_file,
				g_strerror(errno));

		return -1;
	}

	pid_str = g_strdup_printf("%d", getpid());

	if (write(fd, pid_str, strlen(pid_str)) < 0) {
		g_set_error(gerr,
				G_FILE_ERROR,
				g_file_error_from_errno(errno),
				"%s: write(%s) of %s failed: %s", 
				G_STRLOC,
				pid_file,
				pid_str,
				g_strerror(errno));
		ret = -1;
	}
	g_free(pid_str);

	close(fd);

	return ret;
}
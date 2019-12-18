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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ cleanup_old_pidfile (char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int getpid () ; 
 int /*<<< orphan*/ * pidfile_path ; 
 int pidfile_pid ; 
 int register_atexit_handler () ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static int
create_pidfile(const char* path)
{
	FILE *f;

	if (register_atexit_handler() == -1)
		return -1;

	if (cleanup_old_pidfile(path) == 0)
		return 0;

	pidfile_path = strdup(path);
	if (pidfile_path == NULL)
		return -1;

	if ((f = fopen(path, "w")) == NULL) {
		free(pidfile_path);
		pidfile_path = NULL;
		return -1;
	}

	pidfile_pid = getpid();

	(void) fprintf(f, "%d\n", pidfile_pid);
	(void) fclose(f);

	return 0;
}
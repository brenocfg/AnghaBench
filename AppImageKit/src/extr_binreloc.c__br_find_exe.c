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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BrInitError ;

/* Variables and functions */
 int /*<<< orphan*/  BR_INIT_ERROR_DISABLED ; 
 int /*<<< orphan*/  BR_INIT_ERROR_INVALID_MAPS ; 
 int /*<<< orphan*/  BR_INIT_ERROR_NOMEM ; 
 int /*<<< orphan*/  BR_INIT_ERROR_OPEN_MAPS ; 
 int /*<<< orphan*/  BR_INIT_ERROR_READ_MAPS ; 
 int PATH_MAX ; 
 int SSIZE_MAX ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int readlink (char*,char*,size_t) ; 
 scalar_t__ realloc (char*,size_t) ; 
 int stat (char*,struct stat*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 

__attribute__((used)) static char *
_br_find_exe (BrInitError *error)
{
#ifndef ENABLE_BINRELOC
	if (error)
		*error = BR_INIT_ERROR_DISABLED;
	return NULL;
#else
	char *path, *path2, *line, *result;
	size_t buf_size;
	ssize_t size;
	struct stat stat_buf;
	FILE *f;

	/* Read from /proc/self/exe (symlink) */
	if (sizeof (path) > SSIZE_MAX)
		buf_size = SSIZE_MAX - 1;
	else
		buf_size = PATH_MAX - 1;
	path = (char *) malloc (buf_size);
	if (path == NULL) {
		/* Cannot allocate memory. */
		if (error)
			*error = BR_INIT_ERROR_NOMEM;
		return NULL;
	}
	path2 = (char *) malloc (buf_size);
	if (path2 == NULL) {
		/* Cannot allocate memory. */
		if (error)
			*error = BR_INIT_ERROR_NOMEM;
		free (path);
		return NULL;
	}

	strncpy (path2, "/proc/self/exe", buf_size - 1);

	while (1) {
		int i;

		size = readlink (path2, path, buf_size - 1);
		if (size == -1) {
			/* Error. */
			free (path2);
			break;
		}

		/* readlink() success. */
		path[size] = '\0';

		/* Check whether the symlink's target is also a symlink.
		 * We want to get the final target. */
		i = stat (path, &stat_buf);
		if (i == -1) {
			/* Error. */
			free (path2);
			break;
		}

		/* stat() success. */
		if (!S_ISLNK (stat_buf.st_mode)) {
			/* path is not a symlink. Done. */
			free (path2);
			return path;
		}

		/* path is a symlink. Continue loop and resolve this. */
		strncpy (path, path2, buf_size - 1);
	}


	/* readlink() or stat() failed; this can happen when the program is
	 * running in Valgrind 2.2. Read from /proc/self/maps as fallback. */

	buf_size = PATH_MAX + 128;
	line = (char *) realloc (path, buf_size);
	if (line == NULL) {
		/* Cannot allocate memory. */
		free (path);
		if (error)
			*error = BR_INIT_ERROR_NOMEM;
		return NULL;
	}

	f = fopen ("/proc/self/maps", "r");
	if (f == NULL) {
		free (line);
		if (error)
			*error = BR_INIT_ERROR_OPEN_MAPS;
		return NULL;
	}

	/* The first entry should be the executable name. */
	result = fgets (line, (int) buf_size, f);
	if (result == NULL) {
		fclose (f);
		free (line);
		if (error)
			*error = BR_INIT_ERROR_READ_MAPS;
		return NULL;
	}

	/* Get rid of newline character. */
	buf_size = strlen (line);
	if (buf_size <= 0) {
		/* Huh? An empty string? */
		fclose (f);
		free (line);
		if (error)
			*error = BR_INIT_ERROR_INVALID_MAPS;
		return NULL;
	}
	if (line[buf_size - 1] == 10)
		line[buf_size - 1] = 0;

	/* Extract the filename; it is always an absolute path. */
	path = strchr (line, '/');

	/* Sanity check. */
	if (strstr (line, " r-xp ") == NULL || path == NULL) {
		fclose (f);
		free (line);
		if (error)
			*error = BR_INIT_ERROR_INVALID_MAPS;
		return NULL;
	}

	path = strdup (path);
	free (line);
	fclose (f);
	return path;
#endif /* ENABLE_BINRELOC */
}
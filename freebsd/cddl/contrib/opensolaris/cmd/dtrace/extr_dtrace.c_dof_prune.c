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
struct stat {size_t st_size; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int O_RDONLY ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat (int,struct stat*) ; 
 char* malloc (size_t) ; 
 int open (char const*,int) ; 
 size_t read (int,char*,size_t) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 
 size_t write (int,char*,size_t) ; 

__attribute__((used)) static void
dof_prune(const char *fname)
{
	struct stat sbuf;
	size_t sz, i, j, mark, len;
	char *buf;
	int msg = 0, fd;

	if ((fd = open(fname, O_RDONLY)) == -1) {
		/*
		 * This is okay only if the file doesn't exist at all.
		 */
		if (errno != ENOENT)
			fatal("failed to open %s", fname);
		return;
	}

	if (fstat(fd, &sbuf) == -1)
		fatal("failed to fstat %s", fname);

	if ((buf = malloc((sz = sbuf.st_size) + 1)) == NULL)
		fatal("failed to allocate memory for %s", fname);

	if (read(fd, buf, sz) != sz)
		fatal("failed to read %s", fname);

	buf[sz] = '\0';
	(void) close(fd);

	if ((fd = open(fname, O_WRONLY | O_TRUNC)) == -1)
		fatal("failed to open %s for writing", fname);

	len = strlen("dof-data-");

	for (mark = 0, i = 0; i < sz; i++) {
		if (strncmp(&buf[i], "dof-data-", len) != 0)
			continue;

		/*
		 * This is only a match if it's in the 0th column.
		 */
		if (i != 0 && buf[i - 1] != '\n')
			continue;

		if (msg++ == 0) {
			error("cleaned up old anonymous "
			    "enabling in %s\n", fname);
		}

		/*
		 * We have a match.  First write out our data up until now.
		 */
		if (i != mark) {
			if (write(fd, &buf[mark], i - mark) != i - mark)
				fatal("failed to write to %s", fname);
		}

		/*
		 * Now scan forward until we scan past a newline.
		 */
		for (j = i; j < sz && buf[j] != '\n'; j++)
			continue;

		/*
		 * Reset our mark.
		 */
		if ((mark = j + 1) >= sz)
			break;

		i = j;
	}

	if (mark < sz) {
		if (write(fd, &buf[mark], sz - mark) != sz - mark)
			fatal("failed to write to %s", fname);
	}

	(void) close(fd);
	free(buf);
}
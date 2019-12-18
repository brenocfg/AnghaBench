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
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * ctf_fdopen (int,int*) ; 
 int errno ; 
 int open64 (char const*,int /*<<< orphan*/ ) ; 

ctf_file_t *
ctf_open(const char *filename, int *errp)
{
	ctf_file_t *fp;
	int fd;

	if ((fd = open64(filename, O_RDONLY)) == -1) {
		if (errp != NULL)
			*errp = errno;
		return (NULL);
	}

	fp = ctf_fdopen(fd, errp);
	(void) close(fd);
	return (fp);
}
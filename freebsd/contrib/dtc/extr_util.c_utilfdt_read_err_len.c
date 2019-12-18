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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* xmalloc (int) ; 
 char* xrealloc (char*,int) ; 

int utilfdt_read_err_len(const char *filename, char **buffp, off_t *len)
{
	int fd = 0;	/* assume stdin */
	char *buf = NULL;
	off_t bufsize = 1024, offset = 0;
	int ret = 0;

	*buffp = NULL;
	if (strcmp(filename, "-") != 0) {
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			return errno;
	}

	/* Loop until we have read everything */
	buf = xmalloc(bufsize);
	do {
		/* Expand the buffer to hold the next chunk */
		if (offset == bufsize) {
			bufsize *= 2;
			buf = xrealloc(buf, bufsize);
		}

		ret = read(fd, &buf[offset], bufsize - offset);
		if (ret < 0) {
			ret = errno;
			break;
		}
		offset += ret;
	} while (ret != 0);

	/* Clean up, including closing stdin; return errno on error */
	close(fd);
	if (ret)
		free(buf);
	else
		*buffp = buf;
	*len = bufsize;
	return ret;
}
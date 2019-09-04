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
struct stat {size_t st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFFILEMODE ; 
 int /*<<< orphan*/  EX_NOINPUT ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat (int,struct stat*) ; 
 int ftruncate (int,int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 
 scalar_t__ memcmp (char*,char*,size_t) ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 int read (int,char*,size_t) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 
 int write (int,char*,size_t) ; 

int main(int argc, char * argv[])
{
	struct stat sb;
	char *newcontent = NULL;
	size_t newcontentlength = 0;
	char *oldcontent = NULL;
	int ret;
	int dstfd;
	const char *dst = NULL;
	ssize_t readsize, writesize;
	int i;

	if (argc < 2) {
		usage();
	}

	dst = argv[1];

	for (i=2; i < argc; i++) {
		newcontentlength += strlen(argv[i]) + 1 /* space or newline */;
	}
	newcontentlength += 1; /* NUL */

	newcontent = malloc(newcontentlength);
	if (newcontent == NULL)
		err(EX_UNAVAILABLE, "malloc() failed");

	newcontent[0] = '\0';

	for (i=2; i < argc; i++) {
		strlcat(newcontent, argv[i], newcontentlength);
		if (i < argc - 1) {
			strlcat(newcontent, " ", newcontentlength);
		} else {
			strlcat(newcontent, "\n", newcontentlength);
		}
	}

	dstfd = open(dst, O_RDWR | O_CREAT | O_APPEND, DEFFILEMODE);
	if (dstfd < 0)
		err(EX_NOINPUT, "open(%s)", dst);

	ret = fstat(dstfd, &sb);
	if (ret < 0)
		err(EX_NOINPUT, "fstat(%s)", dst);

	if (!S_ISREG(sb.st_mode))
		err(EX_USAGE, "%s is not a regular file", dst);

	if (sb.st_size != newcontentlength) {
		/* obvious new content must be different than old */
		goto replace;
	}

	oldcontent = malloc(newcontentlength);
	if (oldcontent == NULL)
		err(EX_UNAVAILABLE, "malloc(%lu) failed", newcontentlength);

	readsize = read(dstfd, oldcontent, newcontentlength);
	if (readsize == -1)
		err(EX_UNAVAILABLE, "read() failed");
	else if (readsize != newcontentlength)
		errx(EX_UNAVAILABLE, "short read of file");

	if (0 == memcmp(oldcontent, newcontent, newcontentlength)) {
		/* binary comparison succeeded, just exit */
		free(oldcontent);
		ret = close(dstfd);
		if (ret < 0)
			err(EX_UNAVAILABLE, "close() failed");

		exit(0);
	}

replace:
	ret = ftruncate(dstfd, 0);
	if (ret < 0)
		err(EX_UNAVAILABLE, "ftruncate() failed");

	writesize = write(dstfd, newcontent, newcontentlength);
	if (writesize == -1)
		err(EX_UNAVAILABLE, "write() failed");
	else if (writesize != newcontentlength)
		errx(EX_UNAVAILABLE, "short write of file");

	ret = close(dstfd);
	if (ret < 0)
		err(EX_NOINPUT, "close(dst)");

	return 0;
}
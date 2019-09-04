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
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  dsttmpname ;

/* Variables and functions */
 int /*<<< orphan*/  COPYFILE_DATA ; 
 int /*<<< orphan*/  EX_NOINPUT ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int MAXPATHLEN ; 
 int O_RDONLY ; 
 int O_SYMLINK ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int fchmod (int,int /*<<< orphan*/ ) ; 
 int fcopyfile (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int fstat (int,struct stat*) ; 
 int futimes (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getmode (void*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int mkstemp (char*) ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int rename (char*,char const*) ; 
 void* setmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char * argv[])
{
	struct stat sb;
	void *mset;
	mode_t mode;
	bool gotmode = false;
	int ch;
	int ret;
	int srcfd, dstfd;
	const char *src = NULL;
	const char *dst = NULL;
	char dsttmpname[MAXPATHLEN];

	while ((ch = getopt(argc, argv, "cSm:")) != -1) {
		switch(ch) {
			case 'c':
			case 'S':
				/* ignored for compatibility */
				break;
			case 'm':
				gotmode = true;
				mset = setmode(optarg);
				if (!mset)
					errx(EX_USAGE, "Unrecognized mode %s", optarg);

				mode = getmode(mset, 0);
				free(mset);
				break;
			case '?':
			default:
				usage();
		}
	}

	argc -= optind;
	argv += optind;

	if (argc < 2) {
		usage();
	}

	src = argv[0];
	dst = argv[1];

	srcfd = open(src, O_RDONLY | O_SYMLINK, 0);
	if (srcfd < 0)
		err(EX_NOINPUT, "open(%s)", src);

	ret = fstat(srcfd, &sb);
	if (ret < 0)
		err(EX_NOINPUT, "fstat(%s)", src);

	if (!S_ISREG(sb.st_mode))
		err(EX_USAGE, "%s is not a regular file", src);

	snprintf(dsttmpname, sizeof(dsttmpname), "%s.XXXXXX", dst);

	dstfd = mkstemp(dsttmpname);
	if (dstfd < 0)
		err(EX_UNAVAILABLE, "mkstemp(%s)", dsttmpname);

	ret = fcopyfile(srcfd, dstfd, NULL,
					COPYFILE_DATA);
	if (ret < 0)
		err(EX_UNAVAILABLE, "fcopyfile(%s, %s)", src, dsttmpname);

	ret = futimes(dstfd, NULL);
	if (ret < 0)
		err(EX_UNAVAILABLE, "futimes(%s)", dsttmpname);

	if (gotmode) {
		ret = fchmod(dstfd, mode);
		if (ret < 0)
			err(EX_NOINPUT, "fchmod(%s, %ho)", dsttmpname, mode);
	}

	ret = rename(dsttmpname, dst);
	if (ret < 0)
		err(EX_NOINPUT, "rename(%s, %s)", dsttmpname, dst);

	ret = close(dstfd);
	if (ret < 0)
		err(EX_NOINPUT, "close(dst)");

	ret = close(srcfd);
	if (ret < 0)
		err(EX_NOINPUT, "close(src)");

	return 0;
}
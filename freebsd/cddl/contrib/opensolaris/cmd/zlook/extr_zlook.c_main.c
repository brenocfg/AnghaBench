#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int zl_reqflags; int zr_reqflags; char* zr_dir; char* zr_file; long zr_buflen; int zr_retcode; char* zl_dir; char* zl_file; char* zl_xfile; int zl_retcode; int zl_deflags; char* zl_real; int /*<<< orphan*/  zl_xvattrs; int /*<<< orphan*/  zl_statbuf; int /*<<< orphan*/  zr_eof; scalar_t__ zr_buf; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ zut_readdir_t ;
typedef  TYPE_1__ zut_lookup_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 long BIGBUF ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENXIO ; 
 long LILBUF ; 
 long MAXBUF ; 
 int MAXNAMELEN ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int ZUT_ACCFILTER ; 
 char* ZUT_DEV ; 
 int ZUT_EXTRDDIR ; 
 int ZUT_GETSTAT ; 
 int ZUT_IGNORECASE ; 
 int /*<<< orphan*/  ZUT_IOC_LOOKUP ; 
 int /*<<< orphan*/  ZUT_IOC_READDIR ; 
 int ZUT_XATTR ; 
#define  _PC_ACCESS_FILTERING 130 
#define  _PC_SATTR_ENABLED 129 
#define  _PC_SATTR_EXISTS 128 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* malloc (long) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 long pathconf (char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  print_entries (TYPE_1__*) ; 
 int /*<<< orphan*/  print_extd_entries (TYPE_1__*) ; 
 int /*<<< orphan*/  print_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_xvs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 long strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char **argv)
{
	zut_lookup_t lk = {0};
	zut_readdir_t rd = {0};
	boolean_t checking = B_FALSE;
	boolean_t looking = B_FALSE;
	boolean_t reading = B_FALSE;
	boolean_t bflag = B_FALSE;
	long rddir_bufsize = BIGBUF;
	int error = 0;
	int check;
	int fd;
	int c;

	while ((c = getopt(argc, argv, "lisaerb:ASE")) != -1) {
		switch (c) {
		case 'l':
			looking = B_TRUE;
			break;
		case 'i':
			lk.zl_reqflags |= ZUT_IGNORECASE;
			looking = B_TRUE;
			break;
		case 's':
			lk.zl_reqflags |= ZUT_GETSTAT;
			looking = B_TRUE;
			break;
		case 'a':
			rd.zr_reqflags |= ZUT_ACCFILTER;
			reading = B_TRUE;
			break;
		case 'e':
			rd.zr_reqflags |= ZUT_EXTRDDIR;
			reading = B_TRUE;
			break;
		case 'r':
			reading = B_TRUE;
			break;
		case 'b':
			reading = B_TRUE;
			bflag = B_TRUE;
			rddir_bufsize = strtol(optarg, NULL, 0);
			break;
		case 'A':
			checking = B_TRUE;
			check = _PC_ACCESS_FILTERING;
			break;
		case 'S':
			checking = B_TRUE;
			check = _PC_SATTR_ENABLED;
			break;
		case 'E':
			checking = B_TRUE;
			check = _PC_SATTR_EXISTS;
			break;
		case '?':
		default:
			usage(argv[0]);		/* no return */
		}
	}

	if ((checking && looking) || (checking && reading) ||
	    (looking && reading) || (!reading && bflag) ||
	    (!checking && !reading && !looking))
		usage(argv[0]);		/* no return */

	if (rddir_bufsize < LILBUF || rddir_bufsize > MAXBUF) {
		(void) fprintf(stderr, "Sorry, buffer size "
		    "must be >= %d and less than or equal to %d bytes.\n",
		    (int)LILBUF, MAXBUF);
		exit(EINVAL);
	}

	if (checking) {
		char pathbuf[MAXPATHLEN];
		long result;

		if (argc - optind < 1)
			usage(argv[0]);		/* no return */
		(void) strlcpy(pathbuf, argv[optind], MAXPATHLEN);
		result = pathconf(pathbuf, check);
		(void) printf("pathconf(2) check for %s\n", pathbuf);
		switch (check) {
		case _PC_SATTR_ENABLED:
			(void) printf("System attributes ");
			if (result != 0)
				(void) printf("Enabled\n");
			else
				(void) printf("Not enabled\n");
			break;
		case _PC_SATTR_EXISTS:
			(void) printf("System attributes ");
			if (result != 0)
				(void) printf("Exist\n");
			else
				(void) printf("Do not exist\n");
			break;
		case _PC_ACCESS_FILTERING:
			(void) printf("Access filtering ");
			if (result != 0)
				(void) printf("Available\n");
			else
				(void) printf("Not available\n");
			break;
		}
		return (result);
	}

	if ((fd = open(ZUT_DEV, O_RDONLY)) < 0) {
		perror(ZUT_DEV);
		return (ENXIO);
	}

	if (reading) {
		char *buf;

		if (argc - optind < 1)
			usage(argv[0]);		/* no return */

		(void) strlcpy(rd.zr_dir, argv[optind], MAXPATHLEN);
		if (argc - optind > 1) {
			(void) strlcpy(rd.zr_file, argv[optind + 1],
			    MAXNAMELEN);
			rd.zr_reqflags |= ZUT_XATTR;
		}

		if ((buf = malloc(rddir_bufsize)) == NULL) {
			error = errno;
			perror("malloc");
			(void) close(fd);
			return (error);
		}

		rd.zr_buf = (uint64_t)(uintptr_t)buf;
		rd.zr_buflen = rddir_bufsize;

		while (!rd.zr_eof) {
			int ierr;

			if ((ierr = ioctl(fd, ZUT_IOC_READDIR, &rd)) != 0) {
				(void) fprintf(stderr,
				    "IOCTL error: %s (%d)\n",
				    strerror(ierr), ierr);
				free(buf);
				(void) close(fd);
				return (ierr);
			}
			if (rd.zr_retcode) {
				(void) fprintf(stderr,
				    "readdir result: %s (%d)\n",
				    strerror(rd.zr_retcode), rd.zr_retcode);
				free(buf);
				(void) close(fd);
				return (rd.zr_retcode);
			}
			if (rd.zr_reqflags & ZUT_EXTRDDIR)
				print_extd_entries(&rd);
			else
				print_entries(&rd);
		}
		free(buf);
	} else {
		int ierr;

		if (argc - optind < 2)
			usage(argv[0]);		/* no return */

		(void) strlcpy(lk.zl_dir, argv[optind], MAXPATHLEN);
		(void) strlcpy(lk.zl_file, argv[optind + 1], MAXNAMELEN);
		if (argc - optind > 2) {
			(void) strlcpy(lk.zl_xfile,
			    argv[optind + 2], MAXNAMELEN);
			lk.zl_reqflags |= ZUT_XATTR;
		}

		if ((ierr = ioctl(fd, ZUT_IOC_LOOKUP, &lk)) != 0) {
			(void) fprintf(stderr,
			    "IOCTL error: %s (%d)\n",
			    strerror(ierr), ierr);
			(void) close(fd);
			return (ierr);
		}

		(void) printf("\nLookup of ");
		if (lk.zl_reqflags & ZUT_XATTR) {
			(void) printf("extended attribute \"%s\" of ",
			    lk.zl_xfile);
		}
		(void) printf("file \"%s\" ", lk.zl_file);
		(void) printf("in directory \"%s\" ", lk.zl_dir);
		if (lk.zl_retcode) {
			(void) printf("failed: %s (%d)\n",
			    strerror(lk.zl_retcode), lk.zl_retcode);
			(void) close(fd);
			return (lk.zl_retcode);
		}

		(void) printf("succeeded.\n");
		if (lk.zl_reqflags & ZUT_IGNORECASE) {
			(void) printf("----------------------------\n");
			(void) printf("dirent flags: 0x%0x\n", lk.zl_deflags);
			(void) printf("real name: %s\n", lk.zl_real);
		}
		if (lk.zl_reqflags & ZUT_GETSTAT) {
			(void) printf("----------------------------\n");
			print_stats(&lk.zl_statbuf);
			print_xvs(lk.zl_xvattrs);
		}
	}

	(void) close(fd);
	return (0);
}
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
#define  APPND 131 
#define  ARCHIVE 130 
 int /*<<< orphan*/  BZIP2_CMD ; 
 int /*<<< orphan*/  COMPRESS_CMD ; 
 char* DEV_0 ; 
 char* DEV_1 ; 
 char* DEV_4 ; 
 char* DEV_5 ; 
 char* DEV_7 ; 
 char* DEV_8 ; 
#define  EXTRACT 129 
 size_t F_OTAR ; 
 size_t F_TAR ; 
 int /*<<< orphan*/  GZIP_CMD ; 
 int Hflag ; 
#define  LIST 128 
 int Lflag ; 
 int Xflag ; 
 char* _PATH_DEFTAPE ; 
 int act ; 
 char* arcname ; 
 char* chdname ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * frmt ; 
 int /*<<< orphan*/ * fsub ; 
 int /*<<< orphan*/  ftree_add (char*,int) ; 
 char* get_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_line_error ; 
 char* getenv (char*) ; 
 int getoldopt (int,char**,char*) ; 
 int /*<<< orphan*/  gzip_program ; 
 int iflag ; 
 int /*<<< orphan*/  listf ; 
 int /*<<< orphan*/  maxflt ; 
 int nflag ; 
 int /*<<< orphan*/  opt_add (char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  pat_add (char*,char*) ; 
 int /*<<< orphan*/  paxwarn (int,char*,...) ; 
 int pids ; 
 int pmode ; 
 int pmtime ; 
 struct incfile* realloc (struct incfile*,int) ; 
 int /*<<< orphan*/  rep_add (char*) ; 
 int rmleadslash ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ str_offt (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  tar_usage () ; 
 int /*<<< orphan*/  vflag ; 
 int wrblksz ; 

__attribute__((used)) static void
tar_options(int argc, char **argv)
{
	int c;
	int fstdin = 0;
	int tar_Oflag = 0;
	int nincfiles = 0;
	int incfiles_max = 0;
	struct incfile {
		char *file;
		char *dir;
	};
	struct incfile *incfiles = NULL;

	/*
	 * Set default values.
	 */
	rmleadslash = 1;

	/*
	 * process option flags
	 */
	while ((c = getoldopt(argc, argv,
	    "b:cef:hjmopqruts:vwxyzBC:HI:LOPXZ014578")) != -1) {
		switch(c) {
		case 'b':
			/*
			 * specify blocksize in 512-byte blocks
			 */
			if ((wrblksz = (int)str_offt(optarg)) <= 0) {
				paxwarn(1, "Invalid block size %s", optarg);
				tar_usage();
			}
			wrblksz *= 512;		/* XXX - check for int oflow */
			break;
		case 'c':
			/*
			 * create an archive
			 */
			act = ARCHIVE;
			break;
		case 'e':
			/*
			 * stop after first error
			 */
			maxflt = 0;
			break;
		case 'f':
			/*
			 * filename where the archive is stored
			 */
			if ((optarg[0] == '-') && (optarg[1]== '\0')) {
				/*
				 * treat a - as stdin
				 */
				fstdin = 1;
				arcname = NULL;
				break;
			}
			fstdin = 0;
			arcname = optarg;
			break;
		case 'h':
			/*
			 * follow symlinks
			 */
			Lflag = 1;
			break;
		case 'j':
		case 'y':
			/*
			 * use bzip2.  Non standard option.
			 */
			gzip_program = BZIP2_CMD;
			break;
		case 'm':
			/*
			 * do not preserve modification time
			 */
			pmtime = 0;
			break;
		case 'o':
			if (opt_add("write_opt=nodir") < 0)
				tar_usage();
		case 'O':
			tar_Oflag = 1;
			break;
		case 'p':
			/*
			 * preserve uid/gid and file mode, regardless of umask
			 */
			pmode = 1;
			pids = 1;
			break;
		case 'q':
			/*
			 * select first match for a pattern only
			 */
			nflag = 1;
			break;
		case 'r':
		case 'u':
			/*
			 * append to the archive
			 */
			act = APPND;
			break;
		case 's':
			/*
			 * file name substitution name pattern
			 */
			if (rep_add(optarg) < 0) {
				tar_usage();
				break;
			}
			break;
		case 't':
			/*
			 * list contents of the tape
			 */
			act = LIST;
			break;
		case 'v':
			/*
			 * verbose operation mode
			 */
			vflag++;
			break;
		case 'w':
			/*
			 * interactive file rename
			 */
			iflag = 1;
			break;
		case 'x':
			/*
			 * extract an archive, preserving mode,
			 * and mtime if possible.
			 */
			act = EXTRACT;
			pmtime = 1;
			break;
		case 'z':
			/*
			 * use gzip.  Non standard option.
			 */
			gzip_program = GZIP_CMD;
			break;
		case 'B':
			/*
			 * Nothing to do here, this is pax default
			 */
			break;
		case 'C':
			chdname = optarg;
			break;
		case 'H':
			/*
			 * follow command line symlinks only
			 */
			Hflag = 1;
			break;
		case 'I':
			if (++nincfiles > incfiles_max) {
				incfiles_max = nincfiles + 3;
				incfiles = realloc(incfiles,
				    sizeof(*incfiles) * incfiles_max);
				if (incfiles == NULL) {
					paxwarn(0, "Unable to allocate space "
					    "for option list");
					exit(1);
				}
			}
			incfiles[nincfiles - 1].file = optarg;
			incfiles[nincfiles - 1].dir = chdname;
			break;
		case 'L':
			/*
			 * follow symlinks
			 */
			Lflag = 1;
			break;
		case 'P':
			/*
			 * do not remove leading '/' from pathnames
			 */
			rmleadslash = 0;
			break;
		case 'X':
			/*
			 * do not pass over mount points in the file system
			 */
			Xflag = 1;
			break;
		case 'Z':
			/*
			 * use compress.
			 */
			gzip_program = COMPRESS_CMD;
			break;
		case '0':
			arcname = DEV_0;
			break;
		case '1':
			arcname = DEV_1;
			break;
		case '4':
			arcname = DEV_4;
			break;
		case '5':
			arcname = DEV_5;
			break;
		case '7':
			arcname = DEV_7;
			break;
		case '8':
			arcname = DEV_8;
			break;
		default:
			tar_usage();
			break;
		}
	}
	argc -= optind;
	argv += optind;

	/* Traditional tar behaviour (pax uses stderr unless in list mode) */
	if (fstdin == 1 && act == ARCHIVE)
		listf = stderr;
	else
		listf = stdout;

	/* Traditional tar behaviour (pax wants to read file list from stdin) */
	if ((act == ARCHIVE || act == APPND) && argc == 0 && nincfiles == 0)
		exit(0);

	/*
	 * if we are writing (ARCHIVE) specify tar, otherwise run like pax
	 * (unless -o specified)
	 */
	if (act == ARCHIVE || act == APPND)
		frmt = &(fsub[tar_Oflag ? F_OTAR : F_TAR]);
	else if (tar_Oflag) {
		paxwarn(1, "The -O/-o options are only valid when writing an archive");
		tar_usage();		/* only valid when writing */
	}

	/*
	 * process the args as they are interpreted by the operation mode
	 */
	switch (act) {
	case LIST:
	case EXTRACT:
	default:
		{
			int sawpat = 0;
			char *file, *dir = NULL;

			while (nincfiles || *argv != NULL) {
				/*
				 * If we queued up any include files,
				 * pull them in now.  Otherwise, check
				 * for -I and -C positional flags.
				 * Anything else must be a file to
				 * extract.
				 */
				if (nincfiles) {
					file = incfiles->file;
					dir = incfiles->dir;
					incfiles++;
					nincfiles--;
				} else if (strcmp(*argv, "-I") == 0) {
					if (*++argv == NULL)
						break;
					file = *argv++;
					dir = chdname;
				} else
					file = NULL;
				if (file != NULL) {
					FILE *fp;
					char *str;

					if (strcmp(file, "-") == 0)
						fp = stdin;
					else if ((fp = fopen(file, "r")) == NULL) {
						paxwarn(1, "Unable to open file '%s' for read", file);
						tar_usage();
					}
					while ((str = get_line(fp)) != NULL) {
						if (pat_add(str, dir) < 0)
							tar_usage();
						sawpat = 1;
					}
					if (strcmp(file, "-") != 0)
						fclose(fp);
					if (get_line_error) {
						paxwarn(1, "Problem with file '%s'", file);
						tar_usage();
					}
				} else if (strcmp(*argv, "-C") == 0) {
					if (*++argv == NULL)
						break;
					chdname = *argv++;
				} else if (pat_add(*argv++, chdname) < 0)
					tar_usage();
				else
					sawpat = 1;
			}
			/*
			 * if patterns were added, we are doing chdir()
			 * on a file-by-file basis, else, just one
			 * global chdir (if any) after opening input.
			 */
			if (sawpat > 0)
				chdname = NULL;	
		}
		break;
	case ARCHIVE:
	case APPND:
		if (chdname != NULL) {	/* initial chdir() */
			if (ftree_add(chdname, 1) < 0)
				tar_usage();
		}

		while (nincfiles || *argv != NULL) {
			char *file, *dir = NULL;

			/*
			 * If we queued up any include files, pull them in
			 * now.  Otherwise, check for -I and -C positional
			 * flags.  Anything else must be a file to include
			 * in the archive.
			 */
			if (nincfiles) {
				file = incfiles->file;
				dir = incfiles->dir;
				incfiles++;
				nincfiles--;
			} else if (strcmp(*argv, "-I") == 0) {
				if (*++argv == NULL)
					break;
				file = *argv++;
				dir = NULL;
			} else
				file = NULL;
			if (file != NULL) {
				FILE *fp;
				char *str;

				/* Set directory if needed */
				if (dir) {
					if (ftree_add(dir, 1) < 0)
						tar_usage();
				}

				if (strcmp(file, "-") == 0)
					fp = stdin;
				else if ((fp = fopen(file, "r")) == NULL) {
					paxwarn(1, "Unable to open file '%s' for read", file);
					tar_usage();
				}
				while ((str = get_line(fp)) != NULL) {
					if (ftree_add(str, 0) < 0)
						tar_usage();
				}
				if (strcmp(file, "-") != 0)
					fclose(fp);
				if (get_line_error) {
					paxwarn(1, "Problem with file '%s'",
					    file);
					tar_usage();
				}
			} else if (strcmp(*argv, "-C") == 0) {
				if (*++argv == NULL)
					break;
				if (ftree_add(*argv++, 1) < 0)
					tar_usage();
			} else if (ftree_add(*argv++, 0) < 0)
				tar_usage();
		}
		/*
		 * no read errors allowed on updates/append operation!
		 */
		maxflt = 0;
		break;
	}
	if (!fstdin && ((arcname == NULL) || (*arcname == '\0'))) {
		arcname = getenv("TAPE");
		if ((arcname == NULL) || (*arcname == '\0'))
			arcname = _PATH_DEFTAPE;
	}
}
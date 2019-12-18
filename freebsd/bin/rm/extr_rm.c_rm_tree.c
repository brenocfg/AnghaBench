#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int st_flags; } ;
struct TYPE_5__ {int fts_info; scalar_t__ fts_errno; char* fts_path; int /*<<< orphan*/  fts_accpath; TYPE_4__* fts_statp; int /*<<< orphan*/  fts_number; } ;
typedef  TYPE_1__ FTSENT ;
typedef  int /*<<< orphan*/  FTS ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
#define  FTS_D 135 
#define  FTS_DNR 134 
#define  FTS_DP 133 
#define  FTS_ERR 132 
#define  FTS_F 131 
 int FTS_NOSTAT ; 
#define  FTS_NS 130 
#define  FTS_NSOK 129 
 int FTS_PHYSICAL ; 
 int /*<<< orphan*/  FTS_SKIP ; 
#define  FTS_W 128 
 int FTS_WHITEOUT ; 
 int FTS_XDEV ; 
 int SF_APPEND ; 
 int SF_IMMUTABLE ; 
 int /*<<< orphan*/  SKIPPED ; 
 int UF_APPEND ; 
 int UF_IMMUTABLE ; 
 scalar_t__ Wflag ; 
 int /*<<< orphan*/  check (char*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char*,int /*<<< orphan*/ ) ; 
 int eval ; 
 scalar_t__ fflag ; 
 int /*<<< orphan*/  fts_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts_open (char**,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* fts_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts_set (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflag ; 
 int /*<<< orphan*/  info ; 
 int lchflags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int rmdir (int /*<<< orphan*/ ) ; 
 scalar_t__ stdin_ok ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  uid ; 
 int undelete (int /*<<< orphan*/ ) ; 
 int unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vflag ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ xflag ; 

__attribute__((used)) static void
rm_tree(char **argv)
{
	FTS *fts;
	FTSENT *p;
	int needstat;
	int flags;
	int rval;

	/*
	 * Remove a file hierarchy.  If forcing removal (-f), or interactive
	 * (-i) or can't ask anyway (stdin_ok), don't stat the file.
	 */
	needstat = !uid || (!fflag && !iflag && stdin_ok);

	/*
	 * If the -i option is specified, the user can skip on the pre-order
	 * visit.  The fts_number field flags skipped directories.
	 */
#define	SKIPPED	1

	flags = FTS_PHYSICAL;
	if (!needstat)
		flags |= FTS_NOSTAT;
	if (Wflag)
		flags |= FTS_WHITEOUT;
	if (xflag)
		flags |= FTS_XDEV;
	if (!(fts = fts_open(argv, flags, NULL))) {
		if (fflag && errno == ENOENT)
			return;
		err(1, "fts_open");
	}
	while ((p = fts_read(fts)) != NULL) {
		switch (p->fts_info) {
		case FTS_DNR:
			if (!fflag || p->fts_errno != ENOENT) {
				warnx("%s: %s",
				    p->fts_path, strerror(p->fts_errno));
				eval = 1;
			}
			continue;
		case FTS_ERR:
			errx(1, "%s: %s", p->fts_path, strerror(p->fts_errno));
		case FTS_NS:
			/*
			 * Assume that since fts_read() couldn't stat the
			 * file, it can't be unlinked.
			 */
			if (!needstat)
				break;
			if (!fflag || p->fts_errno != ENOENT) {
				warnx("%s: %s",
				    p->fts_path, strerror(p->fts_errno));
				eval = 1;
			}
			continue;
		case FTS_D:
			/* Pre-order: give user chance to skip. */
			if (!fflag && !check(p->fts_path, p->fts_accpath,
			    p->fts_statp)) {
				(void)fts_set(fts, p, FTS_SKIP);
				p->fts_number = SKIPPED;
			}
			else if (!uid &&
				 (p->fts_statp->st_flags & (UF_APPEND|UF_IMMUTABLE)) &&
				 !(p->fts_statp->st_flags & (SF_APPEND|SF_IMMUTABLE)) &&
				 lchflags(p->fts_accpath,
					 p->fts_statp->st_flags &= ~(UF_APPEND|UF_IMMUTABLE)) < 0)
				goto err;
			continue;
		case FTS_DP:
			/* Post-order: see if user skipped. */
			if (p->fts_number == SKIPPED)
				continue;
			break;
		default:
			if (!fflag &&
			    !check(p->fts_path, p->fts_accpath, p->fts_statp))
				continue;
		}

		rval = 0;
		if (!uid &&
		    (p->fts_statp->st_flags & (UF_APPEND|UF_IMMUTABLE)) &&
		    !(p->fts_statp->st_flags & (SF_APPEND|SF_IMMUTABLE)))
			rval = lchflags(p->fts_accpath,
				       p->fts_statp->st_flags &= ~(UF_APPEND|UF_IMMUTABLE));
		if (rval == 0) {
			/*
			 * If we can't read or search the directory, may still be
			 * able to remove it.  Don't print out the un{read,search}able
			 * message unless the remove fails.
			 */
			switch (p->fts_info) {
			case FTS_DP:
			case FTS_DNR:
				rval = rmdir(p->fts_accpath);
				if (rval == 0 || (fflag && errno == ENOENT)) {
					if (rval == 0 && vflag)
						(void)printf("%s\n",
						    p->fts_path);
					if (rval == 0 && info) {
						info = 0;
						(void)printf("%s\n",
						    p->fts_path);
					}
					continue;
				}
				break;

			case FTS_W:
				rval = undelete(p->fts_accpath);
				if (rval == 0 && (fflag && errno == ENOENT)) {
					if (vflag)
						(void)printf("%s\n",
						    p->fts_path);
					if (info) {
						info = 0;
						(void)printf("%s\n",
						    p->fts_path);
					}
					continue;
				}
				break;

			case FTS_NS:
				/*
				 * Assume that since fts_read() couldn't stat
				 * the file, it can't be unlinked.
				 */
				if (fflag)
					continue;
				/* FALLTHROUGH */

			case FTS_F:
			case FTS_NSOK:
			default:
				rval = unlink(p->fts_accpath);
				if (rval == 0 || (fflag && errno == ENOENT)) {
					if (rval == 0 && vflag)
						(void)printf("%s\n",
						    p->fts_path);
					if (rval == 0 && info) {
						info = 0;
						(void)printf("%s\n",
						    p->fts_path);
					}
					continue;
				}
			}
		}
err:
		warn("%s", p->fts_path);
		eval = 1;
	}
	if (!fflag && errno)
		err(1, "fts_read");
	fts_close(fts);
}
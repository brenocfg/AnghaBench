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
struct statfs {int f_bsize; scalar_t__ f_blocks; scalar_t__ f_bfree; scalar_t__ f_bavail; scalar_t__ f_files; scalar_t__ f_ffree; int /*<<< orphan*/  f_mntonname; int /*<<< orphan*/  f_mntfromname; int /*<<< orphan*/  f_fstypename; } ;
struct maxwidths {int mntfrom; int fstype; int total; int used; int avail; int iused; int ifree; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MNAMELEN ; 
 scalar_t__ Tflag ; 
 int /*<<< orphan*/  fsbtoblk (scalar_t__,int,long) ; 
 char* getbsize (int*,long*) ; 
 scalar_t__ hflag ; 
 scalar_t__ iflag ; 
 void* imax (int,int) ; 
 int /*<<< orphan*/  prthuman (struct statfs*,scalar_t__) ; 
 int /*<<< orphan*/  prthumanvalinode (char*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ thousands ; 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_emit (char const*,...) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 
 int /*<<< orphan*/  xo_warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
prtstat(struct statfs *sfsp, struct maxwidths *mwp)
{
	static long blocksize;
	static int headerlen, timesthrough = 0;
	static const char *header;
	int64_t used, availblks, inodes;
	const char *format;

	if (++timesthrough == 1) {
		mwp->mntfrom = imax(mwp->mntfrom, (int)strlen("Filesystem"));
		mwp->fstype = imax(mwp->fstype, (int)strlen("Type"));
		if (thousands) {		/* make space for commas */
		    mwp->total += (mwp->total - 1) / 3;
		    mwp->used  += (mwp->used - 1) / 3;
		    mwp->avail += (mwp->avail - 1) / 3;
		    mwp->iused += (mwp->iused - 1) / 3;
		    mwp->ifree += (mwp->ifree - 1) / 3;
		}
		if (hflag) {
			header = "   Size";
			mwp->total = mwp->used = mwp->avail =
			    (int)strlen(header);
		} else {
			header = getbsize(&headerlen, &blocksize);
			mwp->total = imax(mwp->total, headerlen);
		}
		mwp->used = imax(mwp->used, (int)strlen("Used"));
		mwp->avail = imax(mwp->avail, (int)strlen("Avail"));

		xo_emit("{T:/%-*s}", mwp->mntfrom, "Filesystem");
		if (Tflag)
			xo_emit("  {T:/%-*s}", mwp->fstype, "Type");
		xo_emit(" {T:/%*s} {T:/%*s} {T:/%*s} {T:Capacity}",
			mwp->total, header,
			mwp->used, "Used", mwp->avail, "Avail");
		if (iflag) {
			mwp->iused = imax(hflag ? 0 : mwp->iused,
			    (int)strlen("  iused"));
			mwp->ifree = imax(hflag ? 0 : mwp->ifree,
			    (int)strlen("ifree"));
			xo_emit(" {T:/%*s} {T:/%*s} {T:\%iused}",
			    mwp->iused - 2, "iused", mwp->ifree, "ifree");
		}
		xo_emit("  {T:Mounted on}\n");
	}

	xo_open_instance("filesystem");
	/* Check for 0 block size.  Can this happen? */
	if (sfsp->f_bsize == 0) {
		xo_warnx ("File system %s does not have a block size, assuming 512.",
		    sfsp->f_mntonname);
		sfsp->f_bsize = 512;
	}
	xo_emit("{tk:name/%-*s}", mwp->mntfrom, sfsp->f_mntfromname);
	if (Tflag)
		xo_emit("  {:type/%-*s}", mwp->fstype, sfsp->f_fstypename);
	used = sfsp->f_blocks - sfsp->f_bfree;
	availblks = sfsp->f_bavail + used;
	if (hflag) {
		prthuman(sfsp, used);
	} else {
		if (thousands)
		    format = " {t:total-blocks/%*j'd} {t:used-blocks/%*j'd} "
			"{t:available-blocks/%*j'd}";
		else
		    format = " {t:total-blocks/%*jd} {t:used-blocks/%*jd} "
			"{t:available-blocks/%*jd}";
		xo_emit(format,
		    mwp->total, fsbtoblk(sfsp->f_blocks,
		    sfsp->f_bsize, blocksize),
		    mwp->used, fsbtoblk(used, sfsp->f_bsize, blocksize),
		    mwp->avail, fsbtoblk(sfsp->f_bavail,
		    sfsp->f_bsize, blocksize));
	}
	xo_emit(" {:used-percent/%5.0f}{U:%%}",
	    availblks == 0 ? 100.0 : (double)used / (double)availblks * 100.0);
	if (iflag) {
		inodes = sfsp->f_files;
		used = inodes - sfsp->f_ffree;
		if (hflag) {
			xo_emit("  ");
			prthumanvalinode(" {:inodes-used/%5s}", used);
			prthumanvalinode(" {:inodes-free/%5s}", sfsp->f_ffree);
		} else {
			if (thousands)
			    format = " {:inodes-used/%*j'd} {:inodes-free/%*j'd}";
			else
			    format = " {:inodes-used/%*jd} {:inodes-free/%*jd}";
			xo_emit(format, mwp->iused, (intmax_t)used,
			    mwp->ifree, (intmax_t)sfsp->f_ffree);
		}
		xo_emit(" {:inodes-used-percent/%4.0f}{U:%%} ",
			inodes == 0 ? 100.0 :
			(double)used / (double)inodes * 100.0);
	} else
		xo_emit("  ");
	if (strncmp(sfsp->f_mntfromname, "total", MNAMELEN) != 0)
		xo_emit("  {:mounted-on}", sfsp->f_mntonname);
	xo_emit("\n");
	xo_close_instance("filesystem");
}
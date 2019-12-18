#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
typedef  scalar_t__ off_t ;
struct TYPE_7__ {scalar_t__ st_mtime; } ;
struct TYPE_9__ {int nlen; TYPE_1__ sb; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int namelen; scalar_t__ seek; scalar_t__ mtime; struct TYPE_8__* fow; } ;
typedef  TYPE_2__ FTM ;
typedef  TYPE_3__ ARCHD ;

/* Variables and functions */
 int /*<<< orphan*/  F_TAB_SZ ; 
 int /*<<< orphan*/  PAXPATHLEN ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ffd ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__** ftab ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 size_t st_hash (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*) ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
chk_ftime(ARCHD *arcn)
{
	FTM *pt;
	int namelen;
	u_int indx;
	char ckname[PAXPATHLEN+1];

	/*
	 * no info, go ahead and add to archive
	 */
	if (ftab == NULL)
		return(0);

	/*
	 * hash the pathname and look up in table
	 */
	namelen = arcn->nlen;
	indx = st_hash(arcn->name, namelen, F_TAB_SZ);
	if ((pt = ftab[indx]) != NULL) {
		/*
		 * the hash chain is not empty, walk down looking for match
		 * only read up the path names if the lengths match, speeds
		 * up the search a lot
		 */
		while (pt != NULL) {
			if (pt->namelen == namelen) {
				/*
				 * potential match, have to read the name
				 * from the scratch file.
				 */
				if (lseek(ffd,pt->seek,SEEK_SET) != pt->seek) {
					syswarn(1, errno,
					    "Failed ftime table seek");
					return(-1);
				}
				if (read(ffd, ckname, namelen) != namelen) {
					syswarn(1, errno,
					    "Failed ftime table read");
					return(-1);
				}

				/*
				 * if the names match, we are done
				 */
				if (!strncmp(ckname, arcn->name, namelen))
					break;
			}

			/*
			 * try the next entry on the chain
			 */
			pt = pt->fow;
		}

		if (pt != NULL) {
			/*
			 * found the file, compare the times, save the newer
			 */
			if (arcn->sb.st_mtime > pt->mtime) {
				/*
				 * file is newer
				 */
				pt->mtime = arcn->sb.st_mtime;
				return(0);
			}
			/*
			 * file is older
			 */
			return(1);
		}
	}

	/*
	 * not in table, add it
	 */
	if ((pt = (FTM *)malloc(sizeof(FTM))) != NULL) {
		/*
		 * add the name at the end of the scratch file, saving the
		 * offset. add the file to the head of the hash chain
		 */
		if ((pt->seek = lseek(ffd, (off_t)0, SEEK_END)) >= 0) {
			if (write(ffd, arcn->name, namelen) == namelen) {
				pt->mtime = arcn->sb.st_mtime;
				pt->namelen = namelen;
				pt->fow = ftab[indx];
				ftab[indx] = pt;
				return(0);
			}
			syswarn(1, errno, "Failed write to file time table");
		} else
			syswarn(1, errno, "Failed seek on file time table");
	} else
		paxwarn(1, "File time table ran out of memory");

	if (pt != NULL)
		free(pt);
	return(-1);
}
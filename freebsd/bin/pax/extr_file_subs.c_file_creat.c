#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int mode_t ;
struct TYPE_4__ {int st_mode; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; TYPE_1__ sb; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ARCHD ;

/* Variables and functions */
 int FILEBITS ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 scalar_t__ chk_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ nodirs ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  syswarn (int,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlnk_exist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
file_creat(ARCHD *arcn)
{
	int fd = -1;
	mode_t file_mode;
	int oerrno;

	/*
	 * assume file doesn't exist, so just try to create it, most times this
	 * works. We have to take special handling when the file does exist. To
	 * detect this, we use O_EXCL. For example when trying to create a
	 * file and a character device or fifo exists with the same name, we
	 * can accidentally open the device by mistake (or block waiting to
	 * open). If we find that the open has failed, then spend the effort
	 * to figure out why. This strategy was found to have better average
	 * performance in common use than checking the file (and the path)
	 * first with lstat.
	 */
	file_mode = arcn->sb.st_mode & FILEBITS;
	if ((fd = open(arcn->name, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL,
	    file_mode)) >= 0)
		return(fd);

	/*
	 * the file seems to exist. First we try to get rid of it (found to be
	 * the second most common failure when traced). If this fails, only
	 * then we go to the expense to check and create the path to the file
	 */
	if (unlnk_exist(arcn->name, arcn->type) != 0)
		return(-1);

	for (;;) {
		/*
		 * try to open it again, if this fails, check all the nodes in
		 * the path and give it a final try. if chk_path() finds that
		 * it cannot fix anything, we will skip the last attempt
		 */
		if ((fd = open(arcn->name, O_WRONLY | O_CREAT | O_TRUNC,
		    file_mode)) >= 0)
			break;
		oerrno = errno;
		if (nodirs || chk_path(arcn->name,arcn->sb.st_uid,arcn->sb.st_gid) < 0) {
			syswarn(1, oerrno, "Unable to create %s", arcn->name);
			return(-1);
		}
	}
	return(fd);
}
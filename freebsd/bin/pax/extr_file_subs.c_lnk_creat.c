#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  ln_name; } ;
typedef  TYPE_1__ ARCHD ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int mk_link (int /*<<< orphan*/ ,struct stat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paxwarn (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
lnk_creat(ARCHD *arcn)
{
	struct stat sb;

	/*
	 * we may be running as root, so we have to be sure that link target
	 * is not a directory, so we lstat and check
	 */
	if (lstat(arcn->ln_name, &sb) < 0) {
		syswarn(1,errno,"Unable to link to %s from %s", arcn->ln_name,
		    arcn->name);
		return(-1);
	}

	if (S_ISDIR(sb.st_mode)) {
		paxwarn(1, "A hard link to the directory %s is not allowed",
		    arcn->ln_name);
		return(-1);
	}

	return(mk_link(arcn->ln_name, &sb, arcn->name, 0));
}
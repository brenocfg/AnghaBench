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
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; } ;
struct TYPE_4__ {scalar_t__ st_dev; scalar_t__ st_ino; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; TYPE_1__ sb; } ;
typedef  TYPE_2__ ARCHD ;

/* Variables and functions */
 scalar_t__ kflag ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  paxwarn (int,char*,int /*<<< orphan*/ ) ; 

int
chk_same(ARCHD *arcn)
{
	struct stat sb;

	/*
	 * if file does not exist, return. if file exists and -k, skip it
	 * quietly
	 */
	if (lstat(arcn->name, &sb) < 0)
		return(1);
	if (kflag)
		return(0);

	/*
	 * better make sure the user does not have src == dest by mistake
	 */
	if ((arcn->sb.st_dev == sb.st_dev) && (arcn->sb.st_ino == sb.st_ino)) {
		paxwarn(1, "Unable to copy %s, file would overwrite itself",
		    arcn->name);
		return(0);
	}
	return(1);
}
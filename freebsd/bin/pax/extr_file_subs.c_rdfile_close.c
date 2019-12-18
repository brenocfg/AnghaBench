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
struct TYPE_4__ {int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_mtime; } ;
struct TYPE_5__ {TYPE_1__ sb; int /*<<< orphan*/  org_name; } ;
typedef  TYPE_2__ ARCHD ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  set_ftime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tflag ; 

void
rdfile_close(ARCHD *arcn, int *fd)
{
	/*
	 * make sure the file is open
	 */
	if (*fd < 0)
		return;

	(void)close(*fd);
	*fd = -1;
	if (!tflag)
		return;

	/*
	 * user wants last access time reset
	 */
	set_ftime(arcn->org_name, arcn->sb.st_mtime, arcn->sb.st_atime, 1);
	return;
}
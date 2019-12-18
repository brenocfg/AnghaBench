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
typedef  int /*<<< orphan*/  llink ;
struct TYPE_5__ {char* p_path; } ;
struct TYPE_4__ {char* fts_path; int /*<<< orphan*/  fts_statp; } ;
typedef  TYPE_1__ FTSENT ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ nflag ; 
 scalar_t__ pflag ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int readlink (char*,char*,int) ; 
 int setfile (int /*<<< orphan*/ ,int) ; 
 scalar_t__ symlink (char*,char*) ; 
 TYPE_2__ to ; 
 scalar_t__ unlink (char*) ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
copy_link(const FTSENT *p, int exists)
{
	int len;
	char llink[PATH_MAX];

	if (exists && nflag) {
		if (vflag)
			printf("%s not overwritten\n", to.p_path);
		return (1);
	}
	if ((len = readlink(p->fts_path, llink, sizeof(llink) - 1)) == -1) {
		warn("readlink: %s", p->fts_path);
		return (1);
	}
	llink[len] = '\0';
	if (exists && unlink(to.p_path)) {
		warn("unlink: %s", to.p_path);
		return (1);
	}
	if (symlink(llink, to.p_path)) {
		warn("symlink: %s", llink);
		return (1);
	}
	return (pflag ? setfile(p->fts_statp, -1) : 0);
}
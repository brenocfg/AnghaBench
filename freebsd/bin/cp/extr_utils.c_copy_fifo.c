#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_2__ {char* p_path; } ;

/* Variables and functions */
 scalar_t__ mkfifo (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ nflag ; 
 scalar_t__ pflag ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int setfile (struct stat*,int) ; 
 TYPE_1__ to ; 
 scalar_t__ unlink (char*) ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
copy_fifo(struct stat *from_stat, int exists)
{

	if (exists && nflag) {
		if (vflag)
			printf("%s not overwritten\n", to.p_path);
		return (1);
	}
	if (exists && unlink(to.p_path)) {
		warn("unlink: %s", to.p_path);
		return (1);
	}
	if (mkfifo(to.p_path, from_stat->st_mode)) {
		warn("mkfifo: %s", to.p_path);
		return (1);
	}
	return (pflag ? setfile(from_stat, -1) : 0);
}
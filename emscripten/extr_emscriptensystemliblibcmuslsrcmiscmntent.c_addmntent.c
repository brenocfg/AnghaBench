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
struct mntent {char* mnt_fsname; char* mnt_dir; char* mnt_type; char* mnt_opts; int mnt_freq; int mnt_passno; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*,char*,char*,char*,int,int) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int addmntent(FILE *f, const struct mntent *mnt)
{
	if (fseek(f, 0, SEEK_END)) return 1;
	return fprintf(f, "%s\t%s\t%s\t%s\t%d\t%d\n",
		mnt->mnt_fsname, mnt->mnt_dir, mnt->mnt_type, mnt->mnt_opts,
		mnt->mnt_freq, mnt->mnt_passno) < 0;
}
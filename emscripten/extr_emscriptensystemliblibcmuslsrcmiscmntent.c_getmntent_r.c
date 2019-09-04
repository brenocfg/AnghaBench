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
struct mntent {char* mnt_fsname; char* mnt_dir; char* mnt_type; char* mnt_opts; int /*<<< orphan*/  mnt_passno; int /*<<< orphan*/  mnt_freq; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscanf (int /*<<< orphan*/ *,char*) ; 
 int sscanf (char*,char*,int*,int*,int*,int*,int*,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 

struct mntent *getmntent_r(FILE *f, struct mntent *mnt, char *linebuf, int buflen)
{
	int cnt, n[8];

	mnt->mnt_freq = 0;
	mnt->mnt_passno = 0;

	do {
		fgets(linebuf, buflen, f);
		if (feof(f) || ferror(f)) return 0;
		if (!strchr(linebuf, '\n')) {
			fscanf(f, "%*[^\n]%*[\n]");
			errno = ERANGE;
			return 0;
		}
		cnt = sscanf(linebuf, " %n%*s%n %n%*s%n %n%*s%n %n%*s%n %d %d",
			n, n+1, n+2, n+3, n+4, n+5, n+6, n+7,
			&mnt->mnt_freq, &mnt->mnt_passno);
	} while (cnt < 2 || linebuf[n[0]] == '#');

	linebuf[n[1]] = 0;
	linebuf[n[3]] = 0;
	linebuf[n[5]] = 0;
	linebuf[n[7]] = 0;

	mnt->mnt_fsname = linebuf+n[0];
	mnt->mnt_dir = linebuf+n[2];
	mnt->mnt_type = linebuf+n[4];
	mnt->mnt_opts = linebuf+n[6];

	return mnt;
}
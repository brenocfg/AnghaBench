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
struct mntent {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct mntent* getmntent_r (int /*<<< orphan*/ *,struct mntent*,char*,int) ; 

struct mntent *getmntent(FILE *f)
{
	static char linebuf[256];
	static struct mntent mnt;
	return getmntent_r(f, &mnt, linebuf, sizeof linebuf);
}
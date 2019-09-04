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
struct mntent {int /*<<< orphan*/  mnt_opts; } ;

/* Variables and functions */
 char* strstr (int /*<<< orphan*/ ,char const*) ; 

char *hasmntopt(const struct mntent *mnt, const char *opt)
{
	return strstr(mnt->mnt_opts, opt);
}
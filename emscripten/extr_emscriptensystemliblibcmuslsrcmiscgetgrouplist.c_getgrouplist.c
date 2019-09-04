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
struct group {int /*<<< orphan*/  gr_gid; scalar_t__* gr_mem; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  endgrent () ; 
 struct group* getgrent () ; 
 int /*<<< orphan*/  setgrent () ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 

int getgrouplist(const char *user, gid_t gid, gid_t *groups, int *ngroups)
{
	size_t n, i;
	struct group *gr;
	if (*ngroups<1) return -1;
	n = *ngroups;
	*groups++ = gid;
	*ngroups = 1;

	setgrent();
	while ((gr = getgrent()) && *ngroups < INT_MAX) {
		for (i=0; gr->gr_mem[i] && strcmp(user, gr->gr_mem[i]); i++);
		if (!gr->gr_mem[i]) continue;
		if (++*ngroups <= n) *groups++ = gr->gr_gid;
	}
	endgrent();

	return *ngroups > n ? -1 : *ngroups;
}
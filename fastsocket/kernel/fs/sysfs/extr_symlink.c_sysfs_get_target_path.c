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
struct sysfs_dirent {struct sysfs_dirent* s_parent; int /*<<< orphan*/  s_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sysfs_get_target_path(struct sysfs_dirent *parent_sd,
				 struct sysfs_dirent *target_sd, char *path)
{
	struct sysfs_dirent *base, *sd;
	char *s = path;
	int len = 0;

	/* go up to the root, stop at the base */
	base = parent_sd;
	while (base->s_parent) {
		sd = target_sd->s_parent;
		while (sd->s_parent && base != sd)
			sd = sd->s_parent;

		if (base == sd)
			break;

		strcpy(s, "../");
		s += 3;
		base = base->s_parent;
	}

	/* determine end of target string for reverse fillup */
	sd = target_sd;
	while (sd->s_parent && sd != base) {
		len += strlen(sd->s_name) + 1;
		sd = sd->s_parent;
	}

	/* check limits */
	if (len < 2)
		return -EINVAL;
	len--;
	if ((s - path) + len > PATH_MAX)
		return -ENAMETOOLONG;

	/* reverse fillup of target string from target to base */
	sd = target_sd;
	while (sd->s_parent && sd != base) {
		int slen = strlen(sd->s_name);

		len -= slen;
		strncpy(s + len, sd->s_name, slen);
		if (len)
			s[--len] = '/';

		sd = sd->s_parent;
	}

	return 0;
}
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
struct kpersona_info {int* persona_groups; int persona_ngroups; } ;

/* Variables and functions */
 int atoi (char*) ; 

__attribute__((used)) static int parse_groupspec(struct kpersona_info *kinfo, char *spec)
{
	int idx = 0;
	int grp;
	char *s, *e;

	if (!spec)
		return -1;
	s = e = spec;
	while (*s) {
		int comma = 0;
		e = s;
		while (*e && *e != ',')
			e++;
		if (*e)
			comma = 1;
		*e = 0;
		grp = atoi(s);
		if (comma) {
			*e = ',';
			s = e + 1;
		} else {
			s = e;
		}
		if (grp < 0)
			return -1;
		kinfo->persona_groups[idx] = grp;
		idx++;
	}
	kinfo->persona_ngroups = idx;

	return 0;
}
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
struct pf_ruleset {int dummy; } ;
struct pf_anchor {char* owner; struct pf_ruleset ruleset; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 struct pf_anchor* pf_find_anchor (char const*) ; 
 struct pf_ruleset pf_main_ruleset ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

struct pf_ruleset *
pf_find_ruleset_with_owner(const char *path, const char *owner, int is_anchor,
    int *error)
{
	struct pf_anchor	*anchor;

	while (*path == '/')
		path++;
	if (!*path)
		return (&pf_main_ruleset);
	anchor = pf_find_anchor(path);
	if (anchor == NULL) {
		*error = EINVAL;
		return (NULL);
	} else {
		if ((owner && (!strcmp(owner, anchor->owner)))
		    || (is_anchor && !strcmp(anchor->owner, "")))
			return (&anchor->ruleset);
		*error = EPERM;
		return NULL;
	}
}
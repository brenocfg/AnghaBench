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
struct pf_ruleset {TYPE_1__* anchor; } ;
struct pf_rule {int anchor_relative; int anchor_wildcard; TYPE_1__* anchor; } ;
struct TYPE_2__ {char const* path; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  bzero (char*,int /*<<< orphan*/ ) ; 
 struct pf_ruleset* pf_find_or_create_ruleset (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rs_free (char*) ; 
 scalar_t__ rs_malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

int
pf_anchor_setup(struct pf_rule *r, const struct pf_ruleset *s,
    const char *name)
{
	char			*p, *path;
	struct pf_ruleset	*ruleset;

	r->anchor = NULL;
	r->anchor_relative = 0;
	r->anchor_wildcard = 0;
	if (!name[0])
		return (0);
	path = (char *)rs_malloc(MAXPATHLEN);
	bzero(path, MAXPATHLEN);
	if (name[0] == '/')
		strlcpy(path, name + 1, MAXPATHLEN);
	else {
		/* relative path */
		r->anchor_relative = 1;
		if (s->anchor == NULL || !s->anchor->path[0])
			path[0] = 0;
		else
			strlcpy(path, s->anchor->path, MAXPATHLEN);
		while (name[0] == '.' && name[1] == '.' && name[2] == '/') {
			if (!path[0]) {
				printf("pf_anchor_setup: .. beyond root\n");
				rs_free(path);
				return (1);
			}
			if ((p = strrchr(path, '/')) != NULL)
				*p = 0;
			else
				path[0] = 0;
			r->anchor_relative++;
			name += 3;
		}
		if (path[0])
			strlcat(path, "/", MAXPATHLEN);
		strlcat(path, name, MAXPATHLEN);
	}
	if ((p = strrchr(path, '/')) != NULL && strcmp(p, "/*") == 0) {
		r->anchor_wildcard = 1;
		*p = 0;
	}
	ruleset = pf_find_or_create_ruleset(path);
	rs_free(path);
	if (ruleset == NULL || ruleset->anchor == NULL) {
		printf("pf_anchor_setup: ruleset\n");
		return (1);
	}
	r->anchor = ruleset->anchor;
	r->anchor->refcnt++;
	return (0);
}
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
struct pf_anchor {struct pf_ruleset ruleset; } ;

/* Variables and functions */
 struct pf_anchor* pf_find_anchor (char const*) ; 
 struct pf_ruleset pf_main_ruleset ; 

struct pf_ruleset *
pf_find_ruleset(const char *path)
{
	struct pf_anchor	*anchor;

	while (*path == '/')
		path++;
	if (!*path)
		return (&pf_main_ruleset);
	anchor = pf_find_anchor(path);
	if (anchor == NULL)
		return (NULL);
	else
		return (&anchor->ruleset);
}
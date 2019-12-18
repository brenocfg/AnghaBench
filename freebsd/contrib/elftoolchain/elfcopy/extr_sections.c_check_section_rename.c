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
struct section {char* name; char* newname; scalar_t__ loadable; scalar_t__ pseudo; } ;
struct sec_action {char* newname; scalar_t__ rename; } ;
struct elfcopy {char* prefix_alloc; char* prefix_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 struct sec_action* lookup_sec_act (struct elfcopy*,char*,int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
check_section_rename(struct elfcopy *ecp, struct section *s)
{
	struct sec_action *sac;
	char *prefix;
	size_t namelen;

	if (s->pseudo)
		return;

	sac = lookup_sec_act(ecp, s->name, 0);
	if (sac != NULL && sac->rename)
		s->name = sac->newname;

	if (!strcmp(s->name, ".symtab") ||
	    !strcmp(s->name, ".strtab") ||
	    !strcmp(s->name, ".shstrtab"))
		return;

	prefix = NULL;
	if (s->loadable && ecp->prefix_alloc != NULL)
		prefix = ecp->prefix_alloc;
	else if (ecp->prefix_sec != NULL)
		prefix = ecp->prefix_sec;

	if (prefix != NULL) {
		namelen = strlen(s->name) + strlen(prefix) + 1;
		if ((s->newname = malloc(namelen)) == NULL)
			err(EXIT_FAILURE, "malloc failed");
		snprintf(s->newname, namelen, "%s%s", prefix, s->name);
		s->name = s->newname;
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* name; int hits; int /*<<< orphan*/  files; } ;
typedef  TYPE_1__ Path ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIR ; 
 int /*<<< orphan*/ * Hash_FindEntry (int /*<<< orphan*/ *,char const*) ; 
 char* bmake_strdup (char const*) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int hits ; 

__attribute__((used)) static char *
DirLookupAbs(Path *p, const char *name, const char *cp)
{
	char *p1;		/* pointer into p->name */
	const char *p2;		/* pointer into name */

	if (DEBUG(DIR)) {
		fprintf(debug_file, "   %s ...\n", p->name);
	}

	/*
	 * If the file has a leading path component and that component
	 * exactly matches the entire name of the current search
	 * directory, we can attempt another cache lookup. And if we don't
	 * have a hit, we can safely assume the file does not exist at all.
	 */
	for (p1 = p->name, p2 = name; *p1 && *p1 == *p2; p1++, p2++) {
		continue;
	}
	if (*p1 != '\0' || p2 != cp - 1) {
		return NULL;
	}

	if (Hash_FindEntry(&p->files, cp) == NULL) {
		if (DEBUG(DIR)) {
			fprintf(debug_file, "   must be here but isn't -- returning\n");
		}
		/* Return empty string: terminates search */
		return bmake_strdup("");
	}

	p->hits += 1;
	hits += 1;
	if (DEBUG(DIR)) {
		fprintf(debug_file, "   returning %s\n", name);
	}
	return (bmake_strdup(name));
}
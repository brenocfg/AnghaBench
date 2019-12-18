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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  nomem () ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
parseprop(nvlist_t *props, char *propname)
{
	char *propval, *strval;

	if ((propval = strchr(propname, '=')) == NULL) {
		(void) fprintf(stderr, gettext("missing "
		    "'=' for property=value argument\n"));
		return (-1);
	}
	*propval = '\0';
	propval++;
	if (nvlist_lookup_string(props, propname, &strval) == 0) {
		(void) fprintf(stderr, gettext("property '%s' "
		    "specified multiple times\n"), propname);
		return (-1);
	}
	if (nvlist_add_string(props, propname, propval) != 0)
		nomem();
	return (0);
}
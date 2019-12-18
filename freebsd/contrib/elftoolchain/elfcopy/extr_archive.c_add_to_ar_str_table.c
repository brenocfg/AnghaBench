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
struct elfcopy {char* as; int as_cap; size_t as_sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int _INIT_AS_CAP ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 char* malloc (int) ; 
 char* realloc (char*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static void
add_to_ar_str_table(struct elfcopy *ecp, const char *name)
{

	if (ecp->as == NULL) {
		ecp->as_cap = _INIT_AS_CAP;
		ecp->as_sz = 0;
		if ((ecp->as = malloc(ecp->as_cap)) == NULL)
			err(EXIT_FAILURE, "malloc failed");
	}

	/*
	 * The space required for holding one member name in as table includes:
	 * strlen(name) + (1 for '/') + (1 for '\n') + (possibly 1 for padding).
	 */
	while (ecp->as_sz + strlen(name) + 3 > ecp->as_cap) {
		ecp->as_cap *= 2;
		ecp->as = realloc(ecp->as, ecp->as_cap);
		if (ecp->as == NULL)
			err(EXIT_FAILURE, "realloc failed");
	}
	strncpy(&ecp->as[ecp->as_sz], name, strlen(name));
	ecp->as_sz += strlen(name);
	ecp->as[ecp->as_sz++] = '/';
	ecp->as[ecp->as_sz++] = '\n';
}
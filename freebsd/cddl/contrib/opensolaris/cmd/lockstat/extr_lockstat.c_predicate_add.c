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

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
predicate_add(char **pred, char *what, char *cmp, uintptr_t value)
{
	char *new;
	int len, newlen;

	if (what == NULL)
		return;

	if (*pred == NULL) {
		*pred = malloc(1);
		*pred[0] = '\0';
	}

	len = strlen(*pred);
	newlen = len + strlen(what) + 32 + strlen("( && )");
	new = malloc(newlen);

	if (*pred[0] != '\0') {
		if (cmp != NULL) {
			(void) sprintf(new, "(%s) && (%s %s 0x%p)",
			    *pred, what, cmp, (void *)value);
		} else {
			(void) sprintf(new, "(%s) && (%s)", *pred, what);
		}
	} else {
		if (cmp != NULL) {
			(void) sprintf(new, "%s %s 0x%p",
			    what, cmp, (void *)value);
		} else {
			(void) sprintf(new, "%s", what);
		}
	}

	free(*pred);
	*pred = new;
}
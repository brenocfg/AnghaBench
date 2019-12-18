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
typedef  int /*<<< orphan*/  HT ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 char* HT_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,long) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static char *
get_value(char *objtype, HT *objdata, long linenum, char *name)
{
	char *value;

	value = HT_get(objdata, name);
	if (value == NULL) {
		fprintf(stderr,
			"missing property '%s' in section '%s' (line %ld)\n",
			name, objtype, linenum);
		exit(EXIT_FAILURE);
	}
	return value;
}
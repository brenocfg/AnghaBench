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
struct readelf {int /*<<< orphan*/  dop; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/ * ln; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_DEFAULT_OPTIONS ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 TYPE_1__* dwarf_op ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ *) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static void
parse_dwarf_op_long(struct readelf *re, const char *op)
{
	char *p, *token, *bp;
	int i;

	if (op == NULL) {
		re->dop |= DW_DEFAULT_OPTIONS;
		return;
	}

	if ((p = strdup(op)) == NULL)
		err(EXIT_FAILURE, "strdup failed");
	bp = p;

	while ((token = strsep(&p, ",")) != NULL) {
		for (i = 0; dwarf_op[i].ln != NULL; i++) {
			if (!strcmp(token, dwarf_op[i].ln)) {
				re->dop |= dwarf_op[i].value;
				break;
			}
		}
	}

	free(bp);
}
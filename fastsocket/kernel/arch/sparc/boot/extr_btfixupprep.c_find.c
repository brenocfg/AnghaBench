#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; int /*<<< orphan*/ * rel; int /*<<< orphan*/  name; scalar_t__ setinitval; } ;
typedef  TYPE_1__ btfixup ;

/* Variables and functions */
 int MAXSYMS ; 
 TYPE_1__* array ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int last ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static btfixup *find(int type, char *name)
{
	int i;
	for (i = 0; i < last; i++) {
		if (array[i].type == type && !strcmp(array[i].name, name))
			return array + i;
	}
	array[last].type = type;
	array[last].name = strdup(name);
	array[last].setinitval = 0;
	if (!array[last].name) fatal();
	array[last].rel = NULL;
	last++;
	if (last >= MAXSYMS) {
		fprintf(stderr, "Ugh. Something strange. More than %d different BTFIXUP symbols\n", MAXSYMS);
		exit(1);
	}
	return array + last - 1;
}
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
struct TYPE_2__ {int count; int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  LC_ALL ; 
 char* bltinlookup (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* cmdenviron ; 
 int /*<<< orphan*/ * locale_categories ; 
 char** locale_names ; 
 scalar_t__ localevar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  updatecharset () ; 

void
bltinsetlocale(void)
{
	int act = 0;
	char *loc, *locdef;
	int i;

	if (cmdenviron) for (i = 0; i < cmdenviron->count; i++) {
		if (localevar(cmdenviron->args[i])) {
			act = 1;
			break;
		}
	}
	if (!act)
		return;
	loc = bltinlookup("LC_ALL", 0);
	INTOFF;
	if (loc != NULL) {
		setlocale(LC_ALL, loc);
		INTON;
		updatecharset();
		return;
	}
	locdef = bltinlookup("LANG", 0);
	for (i = 0; locale_names[i] != NULL; i++) {
		loc = bltinlookup(locale_names[i], 0);
		if (loc == NULL)
			loc = locdef;
		if (loc != NULL)
			setlocale(locale_categories[i], loc);
	}
	INTON;
	updatecharset();
}
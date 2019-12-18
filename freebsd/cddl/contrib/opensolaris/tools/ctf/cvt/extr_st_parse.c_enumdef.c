#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* t_emem; int /*<<< orphan*/  t_type; } ;
typedef  TYPE_1__ tdesc_t ;
struct TYPE_7__ {char* el_name; struct TYPE_7__* el_next; int /*<<< orphan*/  el_number; } ;
typedef  TYPE_2__ elist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENUM ; 
 int /*<<< orphan*/  expected (char*,char*,char*) ; 
 char* name (char*,char**) ; 
 char* number (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_debug (int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdesc_name (TYPE_1__*) ; 
 TYPE_2__* xcalloc (int) ; 

__attribute__((used)) static void
enumdef(char *cp, tdesc_t **rtdp)
{
	elist_t *elp, **prev;
	char *w;

	(*rtdp)->t_type = ENUM;
	(*rtdp)->t_emem = NULL;

	prev = &((*rtdp)->t_emem);
	while (*cp != ';') {
		elp = xcalloc(sizeof (*elp));
		elp->el_next = NULL;
		*prev = elp;
		cp = name(cp, &w);
		elp->el_name = w;
		cp = number(cp, &elp->el_number);
		parse_debug(3, NULL, "enum %s: %s=%d", tdesc_name(*rtdp),
		    elp->el_name, elp->el_number);
		prev = &elp->el_next;
		if (*cp++ != ',')
			expected("enumdef", ",", cp - 1);
	}
}
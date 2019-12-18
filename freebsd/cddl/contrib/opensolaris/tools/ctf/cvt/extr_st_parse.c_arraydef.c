#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* t_ardef; } ;
typedef  TYPE_1__ tdesc_t ;
typedef  int /*<<< orphan*/  ardef_t ;
struct TYPE_5__ {int ad_nelems; int /*<<< orphan*/  ad_contents; int /*<<< orphan*/  ad_idxtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  expected (char*,char*,char*) ; 
 char* id (char*,int*) ; 
 int /*<<< orphan*/  lookup (int) ; 
 char* number (char*,int*) ; 
 int /*<<< orphan*/  parse_debug (int,char*,char*,int,int,int) ; 
 char* tdefdecl (char*,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* xcalloc (int) ; 

__attribute__((used)) static char *
arraydef(char *cp, tdesc_t **rtdp)
{
	int start, end, h;

	cp = id(cp, &h);
	if (*cp++ != ';')
		expected("arraydef/1", ";", cp - 1);

	(*rtdp)->t_ardef = xcalloc(sizeof (ardef_t));
	(*rtdp)->t_ardef->ad_idxtype = lookup(h);

	cp = number(cp, &start); /* lower */
	if (*cp++ != ';')
		expected("arraydef/2", ";", cp - 1);

	if (*cp == 'S') {
		/*
		 * variable length array - treat as null dimensioned
		 *
		 * For VLA variables on sparc, SS12 generated stab entry
		 * looks as follows:
		 * .stabs "buf:(0,28)=zr(0,4);0;S-12;(0,1)", 0x80, 0, 0, -16
		 * Whereas SS12u1 generated stab entry looks like this:
		 * .stabs "buf:(0,28)=zr(0,4);0;S0;(0,1)", 0x80, 0, 0, 0
		 * On x86, both versions generate the first type of entry.
		 * We should be able to parse both.
		 */
		cp++;
		if (*cp == '-')
			cp++;
		cp = number(cp, &end);
		end = start;
	} else {
		/*
		 * normal fixed-dimension array
		 * Stab entry for this looks as follows :
		 * .stabs "x:(0,28)=ar(0,4);0;9;(0,3)", 0x80, 0, 40, 0
		 */
		cp = number(cp, &end);  /* upper */
	}

	if (*cp++ != ';')
		expected("arraydef/3", ";", cp - 1);
	(*rtdp)->t_ardef->ad_nelems = end - start + 1;
	cp = tdefdecl(cp, h, &((*rtdp)->t_ardef->ad_contents));

	parse_debug(3, cp, "defined array idx type %d %d-%d next ",
	    h, start, end);

	return (cp);
}
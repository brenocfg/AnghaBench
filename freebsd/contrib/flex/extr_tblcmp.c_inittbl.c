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
 void* NIL ; 
 scalar_t__ chk ; 
 int current_max_xpairs ; 
 scalar_t__ firstfree ; 
 int numecs ; 
 scalar_t__ numtemps ; 
 scalar_t__ tblend ; 
 int* tecbck ; 
 int* tecfwd ; 
 scalar_t__ usemecs ; 
 int /*<<< orphan*/  zero_out (char*,size_t) ; 

void    inittbl ()
{
	int i;

	zero_out ((char *) chk,

		  (size_t) (current_max_xpairs * sizeof (int)));

	tblend = 0;
	firstfree = tblend + 1;
	numtemps = 0;

	if (usemecs) {
		/* Set up doubly-linked meta-equivalence classes; these
		 * are sets of equivalence classes which all have identical
		 * transitions out of TEMPLATES.
		 */

		tecbck[1] = NIL;

		for (i = 2; i <= numecs; ++i) {
			tecbck[i] = i - 1;
			tecfwd[i - 1] = i;
		}

		tecfwd[numecs] = NIL;
	}
}
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
 scalar_t__ gentables ; 
 int /*<<< orphan*/  get_int32_decl () ; 
 int num_rules ; 
 int /*<<< orphan*/  out (char*) ; 
 int /*<<< orphan*/  out_dec (char*,int) ; 
 int /*<<< orphan*/  out_str_dec (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  outn (char*) ; 
 scalar_t__* rule_has_nl ; 

__attribute__((used)) static void geneoltbl (void)
{
	int     i;

	outn ("m4_ifdef( [[M4_YY_USE_LINENO]],[[");
	outn ("/* Table of booleans, true if rule could match eol. */");
	out_str_dec (get_int32_decl (), "yy_rule_can_match_eol",
		     num_rules + 1);

	if (gentables) {
		for (i = 1; i <= num_rules; i++) {
			out_dec ("%d, ", rule_has_nl[i] ? 1 : 0);
			/* format nicely, 20 numbers per line. */
			if ((i % 20) == 19)
				out ("\n    ");
		}
		out ("    };\n");
	}
	outn ("]])");
}
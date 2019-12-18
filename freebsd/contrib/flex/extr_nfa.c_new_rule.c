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
 scalar_t__ MAX_RULE ; 
 scalar_t__ MAX_RULES_INCREMENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ current_max_rules ; 
 int /*<<< orphan*/  lerrif (int /*<<< orphan*/ ,scalar_t__) ; 
 int linenum ; 
 int /*<<< orphan*/  num_reallocs ; 
 scalar_t__ num_rules ; 
 int* reallocate_bool_array (int*,scalar_t__) ; 
 int* reallocate_integer_array (int*,scalar_t__) ; 
 int* rule_has_nl ; 
 int* rule_linenum ; 
 int* rule_type ; 
 int* rule_useful ; 

void    new_rule ()
{
	if (++num_rules >= current_max_rules) {
		++num_reallocs;
		current_max_rules += MAX_RULES_INCREMENT;
		rule_type = reallocate_integer_array (rule_type,
						      current_max_rules);
		rule_linenum = reallocate_integer_array (rule_linenum,
							 current_max_rules);
		rule_useful = reallocate_integer_array (rule_useful,
							current_max_rules);
		rule_has_nl = reallocate_bool_array (rule_has_nl,
						     current_max_rules);
	}

	if (num_rules > MAX_RULE)
		lerrif (_("too many rules (> %d)!"), MAX_RULE);

	rule_linenum[num_rules] = linenum;
	rule_useful[num_rules] = false;
	rule_has_nl[num_rules] = false;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sort_dimension {int taken; TYPE_1__* entry; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  err ;
struct TYPE_5__ {int /*<<< orphan*/  list; scalar_t__ se_collapse; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct sort_dimension*) ; 
 int BUFSIZ ; 
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  REG_EXTENDED ; 
 int /*<<< orphan*/  SORT_COMM ; 
 int /*<<< orphan*/  SORT_CPU ; 
 int /*<<< orphan*/  SORT_DSO ; 
 int /*<<< orphan*/  SORT_DSO_FROM ; 
 int /*<<< orphan*/  SORT_DSO_TO ; 
 int /*<<< orphan*/  SORT_MISPREDICT ; 
 int /*<<< orphan*/  SORT_PARENT ; 
 int /*<<< orphan*/  SORT_PID ; 
 int /*<<< orphan*/  SORT_SYM ; 
 int /*<<< orphan*/  SORT_SYM_FROM ; 
 int /*<<< orphan*/  SORT_SYM_TO ; 
 int /*<<< orphan*/  hist_entry__sort_list ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_pattern ; 
 int /*<<< orphan*/  parent_regex ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,char*) ; 
 int regcomp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sort__first_dimension ; 
 int sort__has_parent ; 
 int sort__has_sym ; 
 int sort__need_collapse ; 
 struct sort_dimension* sort_dimensions ; 
 TYPE_1__ sort_parent ; 
 TYPE_1__ sort_sym ; 
 TYPE_1__ sort_sym_from ; 
 TYPE_1__ sort_sym_to ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sort_dimension__add(const char *tok)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(sort_dimensions); i++) {
		struct sort_dimension *sd = &sort_dimensions[i];

		if (strncasecmp(tok, sd->name, strlen(tok)))
			continue;
		if (sd->entry == &sort_parent) {
			int ret = regcomp(&parent_regex, parent_pattern, REG_EXTENDED);
			if (ret) {
				char err[BUFSIZ];

				regerror(ret, &parent_regex, err, sizeof(err));
				pr_err("Invalid regex: %s\n%s", parent_pattern, err);
				return -EINVAL;
			}
			sort__has_parent = 1;
		} else if (sd->entry == &sort_sym ||
			   sd->entry == &sort_sym_from ||
			   sd->entry == &sort_sym_to) {
			sort__has_sym = 1;
		}

		if (sd->taken)
			return 0;

		if (sd->entry->se_collapse)
			sort__need_collapse = 1;

		if (list_empty(&hist_entry__sort_list)) {
			if (!strcmp(sd->name, "pid"))
				sort__first_dimension = SORT_PID;
			else if (!strcmp(sd->name, "comm"))
				sort__first_dimension = SORT_COMM;
			else if (!strcmp(sd->name, "dso"))
				sort__first_dimension = SORT_DSO;
			else if (!strcmp(sd->name, "symbol"))
				sort__first_dimension = SORT_SYM;
			else if (!strcmp(sd->name, "parent"))
				sort__first_dimension = SORT_PARENT;
			else if (!strcmp(sd->name, "cpu"))
				sort__first_dimension = SORT_CPU;
			else if (!strcmp(sd->name, "symbol_from"))
				sort__first_dimension = SORT_SYM_FROM;
			else if (!strcmp(sd->name, "symbol_to"))
				sort__first_dimension = SORT_SYM_TO;
			else if (!strcmp(sd->name, "dso_from"))
				sort__first_dimension = SORT_DSO_FROM;
			else if (!strcmp(sd->name, "dso_to"))
				sort__first_dimension = SORT_DSO_TO;
			else if (!strcmp(sd->name, "mispredict"))
				sort__first_dimension = SORT_MISPREDICT;
		}

		list_add_tail(&sd->entry->list, &hist_entry__sort_list);
		sd->taken = 1;

		return 0;
	}
	return -ESRCH;
}
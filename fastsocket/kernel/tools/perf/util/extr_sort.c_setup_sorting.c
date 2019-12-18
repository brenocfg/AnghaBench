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
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ sort_dimension__add (char*) ; 
 int /*<<< orphan*/  sort_order ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 char* strtok_r (char*,char*,char**) ; 
 int /*<<< orphan*/  usage_with_options (char const* const*,struct option const*) ; 

void setup_sorting(const char * const usagestr[], const struct option *opts)
{
	char *tmp, *tok, *str = strdup(sort_order);

	for (tok = strtok_r(str, ", ", &tmp);
			tok; tok = strtok_r(NULL, ", ", &tmp)) {
		if (sort_dimension__add(tok) < 0) {
			error("Unknown --sort key: `%s'", tok);
			usage_with_options(usagestr, opts);
		}
	}

	free(str);
}
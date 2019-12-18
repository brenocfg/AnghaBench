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
struct parse_events_data__terms {int /*<<< orphan*/ * terms; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PE_START_TERMS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  parse_events__free_terms (int /*<<< orphan*/ *) ; 
 int parse_events__scanner (char const*,struct parse_events_data__terms*,int /*<<< orphan*/ ) ; 

int parse_events_terms(struct list_head *terms, const char *str)
{
	struct parse_events_data__terms data = {
		.terms = NULL,
	};
	int ret;

	ret = parse_events__scanner(str, &data, PE_START_TERMS);
	if (!ret) {
		list_splice(data.terms, terms);
		free(data.terms);
		return 0;
	}

	parse_events__free_terms(data.terms);
	return ret;
}
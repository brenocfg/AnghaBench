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
struct parse_events__term {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_EVENTS__TERM_TYPE_STR ; 
 int new_term (struct parse_events__term**,int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 

int parse_events__term_str(struct parse_events__term **term,
			   int type_term, char *config, char *str)
{
	return new_term(term, PARSE_EVENTS__TERM_TYPE_STR, type_term,
			config, str, 0);
}
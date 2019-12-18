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
typedef  int /*<<< orphan*/  u64 ;
struct parse_events__term {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_EVENTS__TERM_TYPE_NUM ; 
 int new_term (struct parse_events__term**,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int parse_events__term_num(struct parse_events__term **term,
			   int type_term, char *config, u64 num)
{
	return new_term(term, PARSE_EVENTS__TERM_TYPE_NUM, type_term,
			config, NULL, num);
}
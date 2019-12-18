#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  num; int /*<<< orphan*/  str; } ;
struct parse_events__term {TYPE_1__ val; int /*<<< orphan*/  config; int /*<<< orphan*/  type_term; int /*<<< orphan*/  type_val; } ;

/* Variables and functions */
 int new_term (struct parse_events__term**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int parse_events__term_clone(struct parse_events__term **new,
			     struct parse_events__term *term)
{
	return new_term(new, term->type_val, term->type_term, term->config,
			term->val.str, term->val.num);
}
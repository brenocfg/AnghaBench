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
struct TYPE_2__ {char* string; int /*<<< orphan*/  cnt; } ;
struct filter_parse_state {int /*<<< orphan*/  postfix; int /*<<< orphan*/  opstack; struct filter_op* ops; TYPE_1__ infix; } ;
struct filter_op {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct filter_parse_state*,char,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void parse_init(struct filter_parse_state *ps,
		       struct filter_op *ops,
		       char *infix_string)
{
	memset(ps, '\0', sizeof(*ps));

	ps->infix.string = infix_string;
	ps->infix.cnt = strlen(infix_string);
	ps->ops = ops;

	INIT_LIST_HEAD(&ps->opstack);
	INIT_LIST_HEAD(&ps->postfix);
}
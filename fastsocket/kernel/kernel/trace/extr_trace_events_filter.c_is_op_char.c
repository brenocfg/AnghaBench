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
struct filter_parse_state {TYPE_1__* ops; } ;
struct TYPE_2__ {char* string; } ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static inline int is_op_char(struct filter_parse_state *ps, char c)
{
	int i;

	for (i = 0; strcmp(ps->ops[i].string, "OP_NONE"); i++) {
		if (ps->ops[i].string[0] == c)
			return 1;
	}

	return 0;
}
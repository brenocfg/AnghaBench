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
struct filter_parse_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  filter_opstack_empty (struct filter_parse_state*) ; 
 int /*<<< orphan*/  filter_opstack_pop (struct filter_parse_state*) ; 

__attribute__((used)) static void filter_opstack_clear(struct filter_parse_state *ps)
{
	while (!filter_opstack_empty(ps))
		filter_opstack_pop(ps);
}
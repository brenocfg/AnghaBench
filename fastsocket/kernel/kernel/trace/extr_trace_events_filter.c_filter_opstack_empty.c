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
struct filter_parse_state {int /*<<< orphan*/  opstack; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_opstack_empty(struct filter_parse_state *ps)
{
	return list_empty(&ps->opstack);
}
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
struct callchain_list {int /*<<< orphan*/  ms; } ;

/* Variables and functions */
 char map_symbol__folded (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char callchain_list__folded(const struct callchain_list *cl)
{
	return map_symbol__folded(&cl->ms);
}
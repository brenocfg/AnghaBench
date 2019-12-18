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
typedef  int /*<<< orphan*/  line_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSQUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addr_last ; 
 int /*<<< orphan*/  current_addr ; 
 int /*<<< orphan*/ * get_addressed_line_node (int /*<<< orphan*/ ) ; 

void
add_line_node(line_t *lp)
{
	line_t *cp;

	cp = get_addressed_line_node(current_addr);				/* this get_addressed_line_node last! */
	INSQUE(lp, cp);
	addr_last++;
	current_addr++;
}
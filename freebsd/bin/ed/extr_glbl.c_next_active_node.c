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
 size_t active_last ; 
 int /*<<< orphan*/ ** active_list ; 
 size_t active_ptr ; 

line_t *
next_active_node(void)
{
	while (active_ptr < active_last && active_list[active_ptr] == NULL)
		active_ptr++;
	return (active_ptr < active_last) ? active_list[active_ptr++] : NULL;
}
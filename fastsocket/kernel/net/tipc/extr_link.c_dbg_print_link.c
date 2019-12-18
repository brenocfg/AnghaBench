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
struct link {int dummy; } ;

/* Variables and functions */
 scalar_t__ DBG_OUTPUT ; 
 scalar_t__ TIPC_NULL ; 
 int /*<<< orphan*/  link_print (struct link*,scalar_t__,char const*) ; 

__attribute__((used)) static void dbg_print_link(struct link *l_ptr, const char *str)
{
	if (DBG_OUTPUT != TIPC_NULL)
		link_print(l_ptr, DBG_OUTPUT, str);
}
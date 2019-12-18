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
typedef  int u32 ;
struct print_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tipc_printf (struct print_buf*,char*) ; 

__attribute__((used)) static void nametbl_header(struct print_buf *buf, u32 depth)
{
	tipc_printf(buf, "Type       ");

	if (depth > 1)
		tipc_printf(buf, "Lower      Upper      ");
	if (depth > 2)
		tipc_printf(buf, "Port Identity              ");
	if (depth > 3)
		tipc_printf(buf, "Publication");

	tipc_printf(buf, "\n-----------");

	if (depth > 1)
		tipc_printf(buf, "--------------------- ");
	if (depth > 2)
		tipc_printf(buf, "-------------------------- ");
	if (depth > 3)
		tipc_printf(buf, "------------------");

	tipc_printf(buf, "\n");
}
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
typedef  int /*<<< orphan*/  u_char ;
struct sym_ccb {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  spi_print_msg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_print_addr (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void sym_print_msg(struct sym_ccb *cp, char *label, u_char *msg)
{
	if (label)
		sym_print_addr(cp->cmd, "%s: ", label);
	else
		sym_print_addr(cp->cmd, "");

	spi_print_msg(msg);
	printf("\n");
}
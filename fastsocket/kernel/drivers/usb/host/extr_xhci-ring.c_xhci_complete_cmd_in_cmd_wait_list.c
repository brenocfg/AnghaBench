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
typedef  int /*<<< orphan*/  u32 ;
struct xhci_hcd {int dummy; } ;
struct xhci_command {scalar_t__ completion; int /*<<< orphan*/  cmd_list; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_free_command (struct xhci_hcd*,struct xhci_command*) ; 

__attribute__((used)) static void xhci_complete_cmd_in_cmd_wait_list(struct xhci_hcd *xhci,
		struct xhci_command *command, u32 status)
{
	command->status = status;
	list_del(&command->cmd_list);
	if (command->completion)
		complete(command->completion);
	else
		xhci_free_command(xhci, command);
}
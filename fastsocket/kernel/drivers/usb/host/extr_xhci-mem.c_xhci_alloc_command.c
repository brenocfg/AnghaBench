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
struct xhci_hcd {int dummy; } ;
struct xhci_command {int /*<<< orphan*/  cmd_list; scalar_t__ status; void* completion; int /*<<< orphan*/  in_ctx; } ;
struct completion {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XHCI_CTX_TYPE_INPUT ; 
 int /*<<< orphan*/  init_completion (void*) ; 
 int /*<<< orphan*/  kfree (struct xhci_command*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_alloc_container_ctx (struct xhci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_free_container_ctx (struct xhci_hcd*,int /*<<< orphan*/ ) ; 

struct xhci_command *xhci_alloc_command(struct xhci_hcd *xhci,
		bool allocate_in_ctx, bool allocate_completion,
		gfp_t mem_flags)
{
	struct xhci_command *command;

	command = kzalloc(sizeof(*command), mem_flags);
	if (!command)
		return NULL;

	if (allocate_in_ctx) {
		command->in_ctx =
			xhci_alloc_container_ctx(xhci, XHCI_CTX_TYPE_INPUT,
					mem_flags);
		if (!command->in_ctx) {
			kfree(command);
			return NULL;
		}
	}

	if (allocate_completion) {
		command->completion =
			kzalloc(sizeof(struct completion), mem_flags);
		if (!command->completion) {
			xhci_free_container_ctx(xhci, command->in_ctx);
			kfree(command);
			return NULL;
		}
		init_completion(command->completion);
	}

	command->status = 0;
	INIT_LIST_HEAD(&command->cmd_list);
	return command;
}
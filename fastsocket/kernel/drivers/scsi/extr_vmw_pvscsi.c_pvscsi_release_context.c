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
struct pvscsi_ctx {int /*<<< orphan*/  list; int /*<<< orphan*/ * abort_cmp; int /*<<< orphan*/ * cmd; } ;
struct pvscsi_adapter {int /*<<< orphan*/  cmd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pvscsi_release_context(struct pvscsi_adapter *adapter,
				   struct pvscsi_ctx *ctx)
{
	ctx->cmd = NULL;
	ctx->abort_cmp = NULL;
	list_add(&ctx->list, &adapter->cmd_pool);
}
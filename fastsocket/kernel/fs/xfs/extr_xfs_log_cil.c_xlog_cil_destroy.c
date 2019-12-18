#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct log {TYPE_1__* l_cilp; } ;
struct TYPE_2__ {int /*<<< orphan*/  xc_cil; struct TYPE_2__* xc_ctx; scalar_t__ ticket; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_log_ticket_put (scalar_t__) ; 

void
xlog_cil_destroy(
	struct log	*log)
{
	if (!log->l_cilp)
		return;

	if (log->l_cilp->xc_ctx) {
		if (log->l_cilp->xc_ctx->ticket)
			xfs_log_ticket_put(log->l_cilp->xc_ctx->ticket);
		kmem_free(log->l_cilp->xc_ctx);
	}

	ASSERT(list_empty(&log->l_cilp->xc_cil));
	kmem_free(log->l_cilp);
}
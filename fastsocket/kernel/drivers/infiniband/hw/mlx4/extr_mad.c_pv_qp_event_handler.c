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
struct mlx4_ib_demux_pv_ctx {int /*<<< orphan*/  port; } ;
struct ib_event {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pv_qp_event_handler(struct ib_event *event, void *qp_context)
{
	struct mlx4_ib_demux_pv_ctx *sqp = qp_context;

	/* It's worse than that! He's dead, Jim! */
	pr_err("Fatal error (%d) on a MAD QP on port %d\n",
	       event->event, sqp->port);
}
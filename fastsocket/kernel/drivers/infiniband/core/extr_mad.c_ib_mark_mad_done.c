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
struct ib_mad_send_wr_private {int refcount; TYPE_1__* mad_agent_priv; int /*<<< orphan*/  agent_list; scalar_t__ timeout; } ;
struct TYPE_2__ {int /*<<< orphan*/  done_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ib_mark_mad_done(struct ib_mad_send_wr_private *mad_send_wr)
{
	mad_send_wr->timeout = 0;
	if (mad_send_wr->refcount == 1)
		list_move_tail(&mad_send_wr->agent_list,
			      &mad_send_wr->mad_agent_priv->done_list);
}
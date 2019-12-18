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
struct iscsi_cls_session {int /*<<< orphan*/  block_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_eh_timer_workq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void iscsi_block_session(struct iscsi_cls_session *session)
{
	queue_work(iscsi_eh_timer_workq, &session->block_work);
}
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
struct iscsi_tcp_task {int /*<<< orphan*/  r2tpool; int /*<<< orphan*/  r2tqueue; } ;
struct iscsi_task {struct iscsi_tcp_task* dd_data; } ;
struct iscsi_session {int cmds_max; struct iscsi_task** cmds; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_pool_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ ) ; 

void iscsi_tcp_r2tpool_free(struct iscsi_session *session)
{
	int i;

	for (i = 0; i < session->cmds_max; i++) {
		struct iscsi_task *task = session->cmds[i];
		struct iscsi_tcp_task *tcp_task = task->dd_data;

		kfifo_free(tcp_task->r2tqueue);
		iscsi_pool_free(&tcp_task->r2tpool);
	}
}
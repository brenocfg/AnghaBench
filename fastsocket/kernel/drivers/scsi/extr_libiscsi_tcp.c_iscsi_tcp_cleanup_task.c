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
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct iscsi_tcp_task {struct iscsi_r2t_info* r2t; TYPE_1__ r2tpool; int /*<<< orphan*/  r2tqueue; } ;
struct iscsi_task {int /*<<< orphan*/  conn; int /*<<< orphan*/  sc; struct iscsi_tcp_task* dd_data; } ;
struct iscsi_r2t_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_TCP (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ __kfifo_get (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  __kfifo_put (int /*<<< orphan*/ ,void*,int) ; 

void iscsi_tcp_cleanup_task(struct iscsi_task *task)
{
	struct iscsi_tcp_task *tcp_task = task->dd_data;
	struct iscsi_r2t_info *r2t;

	/* nothing to do for mgmt */
	if (!task->sc)
		return;

	/* flush task's r2t queues */
	while (__kfifo_get(tcp_task->r2tqueue, (void*)&r2t, sizeof(void*))) {
		__kfifo_put(tcp_task->r2tpool.queue, (void*)&r2t,
			    sizeof(void*));
		ISCSI_DBG_TCP(task->conn, "pending r2t dropped\n");
	}

	r2t = tcp_task->r2t;
	if (r2t != NULL) {
		__kfifo_put(tcp_task->r2tpool.queue, (void*)&r2t,
			    sizeof(void*));
		tcp_task->r2t = NULL;
	}
}
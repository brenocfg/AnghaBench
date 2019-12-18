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
struct iscsi_task {int /*<<< orphan*/  hdr_itt; } ;
struct cxgbi_task_data {scalar_t__ skb; } ;

/* Variables and functions */
 int CXGBI_DBG_ISCSI ; 
 int /*<<< orphan*/  __kfree_skb (scalar_t__) ; 
 struct cxgbi_task_data* iscsi_task_cxgbi_data (struct iscsi_task*) ; 
 int /*<<< orphan*/  iscsi_tcp_cleanup_task (struct iscsi_task*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct iscsi_task*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cxgbi_task_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  task_release_itt (struct iscsi_task*,int /*<<< orphan*/ ) ; 

void cxgbi_cleanup_task(struct iscsi_task *task)
{
	struct cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);

	log_debug(1 << CXGBI_DBG_ISCSI,
		"task 0x%p, skb 0x%p, itt 0x%x.\n",
		task, tdata->skb, task->hdr_itt);

	/*  never reached the xmit task callout */
	if (tdata->skb)
		__kfree_skb(tdata->skb);
	memset(tdata, 0, sizeof(*tdata));

	task_release_itt(task, task->hdr_itt);
	iscsi_tcp_cleanup_task(task);
}
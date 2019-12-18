#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ip_vs_sync_thread_data {struct ip_vs_sync_thread_data* buf; TYPE_2__* sock; } ;
struct TYPE_5__ {TYPE_1__* sk; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/ * sk_sleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_vs_backup_mcast_ifn ; 
 int /*<<< orphan*/  ip_vs_backup_syncid ; 
 int /*<<< orphan*/  ip_vs_process_message (struct ip_vs_sync_thread_data*,int) ; 
 int ip_vs_receive (TYPE_2__*,struct ip_vs_sync_thread_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ip_vs_sync_thread_data*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_release (TYPE_2__*) ; 
 int /*<<< orphan*/  sync_recv_mesg_maxlen ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sync_thread_backup(void *data)
{
	struct ip_vs_sync_thread_data *tinfo = data;
	int len;

	pr_info("sync thread started: state = BACKUP, mcast_ifn = %s, "
		"syncid = %d\n",
		ip_vs_backup_mcast_ifn, ip_vs_backup_syncid);

	while (!kthread_should_stop()) {
		wait_event_interruptible(*tinfo->sock->sk->sk_sleep,
			 !skb_queue_empty(&tinfo->sock->sk->sk_receive_queue)
			 || kthread_should_stop());

		/* do we have data now? */
		while (!skb_queue_empty(&(tinfo->sock->sk->sk_receive_queue))) {
			len = ip_vs_receive(tinfo->sock, tinfo->buf,
					sync_recv_mesg_maxlen);
			if (len <= 0) {
				pr_err("receiving message error\n");
				break;
			}

			/* disable bottom half, because it accesses the data
			   shared by softirq while getting/creating conns */
			local_bh_disable();
			ip_vs_process_message(tinfo->buf, len);
			local_bh_enable();
		}
	}

	/* release the sending multicast socket */
	sock_release(tinfo->sock);
	kfree(tinfo->buf);
	kfree(tinfo);

	return 0;
}
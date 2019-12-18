#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  i_hdr; struct rds_connection* i_conn; } ;
struct TYPE_3__ {int op_active; } ;
struct rds_message {TYPE_2__ m_inc; int /*<<< orphan*/  m_flags; int /*<<< orphan*/  m_conn_item; TYPE_1__ data; int /*<<< orphan*/  m_daddr; } ;
struct rds_connection {int /*<<< orphan*/  c_send_w; int /*<<< orphan*/  c_flags; int /*<<< orphan*/  c_lock; int /*<<< orphan*/  c_next_tx_seq; int /*<<< orphan*/  c_send_queue; int /*<<< orphan*/  c_fcong; int /*<<< orphan*/  c_faddr; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RDS_LL_SEND_FULL ; 
 int /*<<< orphan*/  RDS_MSG_ON_CONN ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rds_cong_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_conn_connect_if_down (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_message_addref (struct rds_message*) ; 
 struct rds_message* rds_message_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_message_populate_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_message_put (struct rds_message*) ; 
 int /*<<< orphan*/  rds_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_wq ; 
 int /*<<< orphan*/  s_send_pong ; 
 int /*<<< orphan*/  s_send_queued ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
rds_send_pong(struct rds_connection *conn, __be16 dport)
{
	struct rds_message *rm;
	unsigned long flags;
	int ret = 0;

	rm = rds_message_alloc(0, GFP_ATOMIC);
	if (!rm) {
		ret = -ENOMEM;
		goto out;
	}

	rm->m_daddr = conn->c_faddr;
	rm->data.op_active = 1;

	rds_conn_connect_if_down(conn);

	ret = rds_cong_wait(conn->c_fcong, dport, 1, NULL);
	if (ret)
		goto out;

	spin_lock_irqsave(&conn->c_lock, flags);
	list_add_tail(&rm->m_conn_item, &conn->c_send_queue);
	set_bit(RDS_MSG_ON_CONN, &rm->m_flags);
	rds_message_addref(rm);
	rm->m_inc.i_conn = conn;

	rds_message_populate_header(&rm->m_inc.i_hdr, 0, dport,
				    conn->c_next_tx_seq);
	conn->c_next_tx_seq++;
	spin_unlock_irqrestore(&conn->c_lock, flags);

	rds_stats_inc(s_send_queued);
	rds_stats_inc(s_send_pong);

	if (!test_bit(RDS_LL_SEND_FULL, &conn->c_flags))
		queue_delayed_work(rds_wq, &conn->c_send_w, 0);

	rds_message_put(rm);
	return 0;

out:
	if (rm)
		rds_message_put(rm);
	return ret;
}
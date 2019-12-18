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
typedef  scalar_t__ u64 ;
struct rds_iw_connection {int /*<<< orphan*/  conn; int /*<<< orphan*/  i_ack_flags; int /*<<< orphan*/  i_ack_wr; TYPE_1__* i_cm_id; int /*<<< orphan*/  i_ack_queued; struct rds_header* i_ack; } ;
struct rds_header {unsigned int h_credit; int /*<<< orphan*/  h_ack; } ;
struct ib_send_wr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_ACK_IN_FLIGHT ; 
 int /*<<< orphan*/  IB_ACK_REQUESTED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int ib_post_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_send_wr**) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  rds_iw_conn_error (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rds_iw_get_ack (struct rds_iw_connection*) ; 
 int /*<<< orphan*/  rds_iw_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_message_make_checksum (struct rds_header*) ; 
 int /*<<< orphan*/  rds_message_populate_header (struct rds_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_iw_connection*,unsigned long long) ; 
 int /*<<< orphan*/  s_iw_ack_send_failure ; 
 int /*<<< orphan*/  s_iw_ack_sent ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void rds_iw_send_ack(struct rds_iw_connection *ic, unsigned int adv_credits)
{
	struct rds_header *hdr = ic->i_ack;
	struct ib_send_wr *failed_wr;
	u64 seq;
	int ret;

	seq = rds_iw_get_ack(ic);

	rdsdebug("send_ack: ic %p ack %llu\n", ic, (unsigned long long) seq);
	rds_message_populate_header(hdr, 0, 0, 0);
	hdr->h_ack = cpu_to_be64(seq);
	hdr->h_credit = adv_credits;
	rds_message_make_checksum(hdr);
	ic->i_ack_queued = jiffies;

	ret = ib_post_send(ic->i_cm_id->qp, &ic->i_ack_wr, &failed_wr);
	if (unlikely(ret)) {
		/* Failed to send. Release the WR, and
		 * force another ACK.
		 */
		clear_bit(IB_ACK_IN_FLIGHT, &ic->i_ack_flags);
		set_bit(IB_ACK_REQUESTED, &ic->i_ack_flags);

		rds_iw_stats_inc(s_iw_ack_send_failure);

		rds_iw_conn_error(ic->conn, "sending ack failed\n");
	} else
		rds_iw_stats_inc(s_iw_ack_sent);
}
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
struct rds_iw_connection {int /*<<< orphan*/  i_credits; } ;
struct rds_connection {int /*<<< orphan*/  c_send_w; int /*<<< orphan*/  c_flags; struct rds_iw_connection* c_transport_data; } ;

/* Variables and functions */
 int IB_GET_SEND_CREDITS (unsigned int) ; 
 int /*<<< orphan*/  IB_SET_SEND_CREDITS (unsigned int) ; 
 int /*<<< orphan*/  RDS_LL_SEND_FULL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_wq ; 
 int /*<<< orphan*/  rdsdebug (char*,unsigned int,int,char*) ; 
 int /*<<< orphan*/  s_iw_rx_credit_updates ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rds_iw_send_add_credits(struct rds_connection *conn, unsigned int credits)
{
	struct rds_iw_connection *ic = conn->c_transport_data;

	if (credits == 0)
		return;

	rdsdebug("rds_iw_send_add_credits(%u): current=%u%s\n",
			credits,
			IB_GET_SEND_CREDITS(atomic_read(&ic->i_credits)),
			test_bit(RDS_LL_SEND_FULL, &conn->c_flags) ? ", ll_send_full" : "");

	atomic_add(IB_SET_SEND_CREDITS(credits), &ic->i_credits);
	if (test_and_clear_bit(RDS_LL_SEND_FULL, &conn->c_flags))
		queue_delayed_work(rds_wq, &conn->c_send_w, 0);

	WARN_ON(IB_GET_SEND_CREDITS(credits) >= 16384);

	rds_iw_stats_inc(s_iw_rx_credit_updates);
}
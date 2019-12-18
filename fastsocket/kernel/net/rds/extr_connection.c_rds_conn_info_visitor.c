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
struct rds_info_connection {scalar_t__ flags; int /*<<< orphan*/  transport; int /*<<< orphan*/  faddr; int /*<<< orphan*/  laddr; int /*<<< orphan*/  next_rx_seq; int /*<<< orphan*/  next_tx_seq; } ;
struct rds_connection {int /*<<< orphan*/  c_state; int /*<<< orphan*/  c_flags; TYPE_1__* c_trans; int /*<<< orphan*/  c_faddr; int /*<<< orphan*/  c_laddr; int /*<<< orphan*/  c_next_rx_seq; int /*<<< orphan*/  c_next_tx_seq; } ;
struct TYPE_2__ {int /*<<< orphan*/  t_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTED ; 
 int /*<<< orphan*/  CONNECTING ; 
 scalar_t__ RDS_CONN_CONNECTING ; 
 scalar_t__ RDS_CONN_UP ; 
 int /*<<< orphan*/  RDS_IN_XMIT ; 
 int /*<<< orphan*/  SENDING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_conn_info_set (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rds_conn_info_visitor(struct rds_connection *conn,
				  void *buffer)
{
	struct rds_info_connection *cinfo = buffer;

	cinfo->next_tx_seq = conn->c_next_tx_seq;
	cinfo->next_rx_seq = conn->c_next_rx_seq;
	cinfo->laddr = conn->c_laddr;
	cinfo->faddr = conn->c_faddr;
	strncpy(cinfo->transport, conn->c_trans->t_name,
		sizeof(cinfo->transport));
	cinfo->flags = 0;

	rds_conn_info_set(cinfo->flags, test_bit(RDS_IN_XMIT, &conn->c_flags),
			  SENDING);
	/* XXX Future: return the state rather than these funky bits */
	rds_conn_info_set(cinfo->flags,
			  atomic_read(&conn->c_state) == RDS_CONN_CONNECTING,
			  CONNECTING);
	rds_conn_info_set(cinfo->flags,
			  atomic_read(&conn->c_state) == RDS_CONN_UP,
			  CONNECTED);
	return 1;
}
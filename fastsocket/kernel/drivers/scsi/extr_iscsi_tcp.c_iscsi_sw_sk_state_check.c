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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_rmem_alloc; struct iscsi_conn* sk_user_data; } ;
struct iscsi_conn {TYPE_1__* session; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int /*<<< orphan*/  ISCSI_ERR_TCP_CONN_CLOSE ; 
 scalar_t__ ISCSI_STATE_LOGGING_OUT ; 
 int /*<<< orphan*/  ISCSI_SW_TCP_DBG (struct iscsi_conn*,char*) ; 
 scalar_t__ TCP_CLOSE ; 
 scalar_t__ TCP_CLOSE_WAIT ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_conn_failure (struct iscsi_conn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int iscsi_sw_sk_state_check(struct sock *sk)
{
	struct iscsi_conn *conn = sk->sk_user_data;

	if ((sk->sk_state == TCP_CLOSE_WAIT || sk->sk_state == TCP_CLOSE) &&
	    (conn->session->state != ISCSI_STATE_LOGGING_OUT) &&
	    !atomic_read(&sk->sk_rmem_alloc)) {
		ISCSI_SW_TCP_DBG(conn, "TCP_CLOSE|TCP_CLOSE_WAIT\n");
		iscsi_conn_failure(conn, ISCSI_ERR_TCP_CONN_CLOSE);
		return -ECONNRESET;
	}
	return 0;
}
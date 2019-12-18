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
struct iser_conn {scalar_t__ state; int /*<<< orphan*/  wait; } ;
struct iscsi_endpoint {struct iser_conn* dd_data; } ;

/* Variables and functions */
 scalar_t__ ISER_CONN_DOWN ; 
 scalar_t__ ISER_CONN_TERMINATING ; 
 scalar_t__ ISER_CONN_UP ; 
 int /*<<< orphan*/  iser_info (char*,struct iser_conn*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iscsi_iser_ep_poll(struct iscsi_endpoint *ep, int timeout_ms)
{
	struct iser_conn *ib_conn;
	int rc;

	ib_conn = ep->dd_data;
	rc = wait_event_interruptible_timeout(ib_conn->wait,
			     ib_conn->state == ISER_CONN_UP,
			     msecs_to_jiffies(timeout_ms));

	/* if conn establishment failed, return error code to iscsi */
	if (!rc &&
	    (ib_conn->state == ISER_CONN_TERMINATING ||
	     ib_conn->state == ISER_CONN_DOWN))
		rc = -1;

	iser_info("ib conn %p rc = %d\n", ib_conn, rc);

	if (rc > 0)
		return 1; /* success, this is the equivalent of POLLOUT */
	else if (!rc)
		return 0; /* timeout */
	else
		return rc; /* signal */
}
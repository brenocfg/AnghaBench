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
struct TCP_Server_Info {scalar_t__ tcpStatus; int /*<<< orphan*/  req_lock; int /*<<< orphan*/  in_flight; int /*<<< orphan*/  request_q; } ;

/* Variables and functions */
 int const CIFS_ASYNC_OP ; 
 int const CIFS_BLOCKING_OP ; 
 scalar_t__ CifsExiting ; 
 int ENOENT ; 
 int /*<<< orphan*/  cifs_num_waiters_dec (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_num_waiters_inc (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  has_credits (struct TCP_Server_Info*,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_killable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wait_for_free_credits(struct TCP_Server_Info *server, const int optype,
		      int *credits)
{
	int rc;

	spin_lock(&server->req_lock);
	if (optype == CIFS_ASYNC_OP) {
		/* oplock breaks must not be held up */
		server->in_flight++;
		*credits -= 1;
		spin_unlock(&server->req_lock);
		return 0;
	}

	while (1) {
		if (*credits <= 0) {
			spin_unlock(&server->req_lock);
			cifs_num_waiters_inc(server);
			rc = wait_event_killable(server->request_q,
						 has_credits(server, credits));
			cifs_num_waiters_dec(server);
			if (rc)
				return rc;
			spin_lock(&server->req_lock);
		} else {
			if (server->tcpStatus == CifsExiting) {
				spin_unlock(&server->req_lock);
				return -ENOENT;
			}

			/*
			 * Can not count locking commands against total
			 * as they are allowed to block on server.
			 */

			/* update # of requests on the wire to server */
			if (optype != CIFS_BLOCKING_OP) {
				*credits -= 1;
				server->in_flight++;
			}
			spin_unlock(&server->req_lock);
			break;
		}
	}
	return 0;
}
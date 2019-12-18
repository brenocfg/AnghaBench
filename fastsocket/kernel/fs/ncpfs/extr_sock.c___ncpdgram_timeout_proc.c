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
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {struct ncp_request_reply* creq; } ;
struct ncp_server {int timeout_last; int /*<<< orphan*/  timeout_tm; int /*<<< orphan*/  ncp_sock; int /*<<< orphan*/  timeout_retries; TYPE_2__ m; TYPE_1__ rcv; } ;
struct ncp_request_reply {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int NCP_MAX_RPC_TIMEOUT ; 
 int NCP_MOUNT_SOFT ; 
 int /*<<< orphan*/  __ncp_abort_request (struct ncp_server*,struct ncp_request_reply*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ncpdgram_send (int /*<<< orphan*/ ,struct ncp_request_reply*) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ncpdgram_timeout_proc(struct ncp_server *server)
{
	/* If timer is pending, we are processing another request... */
	if (!timer_pending(&server->timeout_tm)) {
		struct ncp_request_reply* req;
		
		req = server->rcv.creq;
		if (req) {
			int timeout;
			
			if (server->m.flags & NCP_MOUNT_SOFT) {
				if (server->timeout_retries-- == 0) {
					__ncp_abort_request(server, req, -ETIMEDOUT);
					return;
				}
			}
			/* Ignore errors */
			ncpdgram_send(server->ncp_sock, req);
			timeout = server->timeout_last << 1;
			if (timeout > NCP_MAX_RPC_TIMEOUT) {
				timeout = NCP_MAX_RPC_TIMEOUT;
			}
			server->timeout_last = timeout;
			mod_timer(&server->timeout_tm, jiffies + timeout);
		}
	}
}
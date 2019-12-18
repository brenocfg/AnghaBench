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
struct ncp_server {int /*<<< orphan*/  rxbuf; } ;
struct ncp_request_reply {int result; scalar_t__ status; int /*<<< orphan*/  wq; int /*<<< orphan*/  datalen; int /*<<< orphan*/  reply_buf; } ;

/* Variables and functions */
 scalar_t__ RQ_ABANDONED ; 
 scalar_t__ RQ_DONE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_req_put (struct ncp_request_reply*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ncp_finish_request(struct ncp_server *server, struct ncp_request_reply *req, int result)
{
	req->result = result;
	if (req->status != RQ_ABANDONED)
		memcpy(req->reply_buf, server->rxbuf, req->datalen);
	req->status = RQ_DONE;
	wake_up_all(&req->wq);
	ncp_req_put(req);
}
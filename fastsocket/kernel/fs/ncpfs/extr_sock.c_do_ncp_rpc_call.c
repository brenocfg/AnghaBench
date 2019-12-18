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
typedef  int /*<<< orphan*/  u_int16_t ;
struct ncp_server {scalar_t__ packet; } ;
struct ncp_request_reply {unsigned char* reply_buf; int datalen; int tx_iovlen; int tx_totallen; scalar_t__ status; int result; int /*<<< orphan*/  wq; int /*<<< orphan*/  tx_type; TYPE_1__* tx_iov; } ;
struct TYPE_2__ {int iov_len; scalar_t__ iov_base; } ;

/* Variables and functions */
 int EINTR ; 
 int ENOMEM ; 
 scalar_t__ RQ_DONE ; 
 int /*<<< orphan*/  ncp_abort_request (struct ncp_server*,struct ncp_request_reply*,int) ; 
 int ncp_add_request (struct ncp_server*,struct ncp_request_reply*) ; 
 struct ncp_request_reply* ncp_alloc_req () ; 
 int /*<<< orphan*/  ncp_req_put (struct ncp_request_reply*) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_ncp_rpc_call(struct ncp_server *server, int size,
		unsigned char* reply_buf, int max_reply_size)
{
	int result;
	struct ncp_request_reply *req;

	req = ncp_alloc_req();
	if (!req)
		return -ENOMEM;

	req->reply_buf = reply_buf;
	req->datalen = max_reply_size;
	req->tx_iov[1].iov_base = server->packet;
	req->tx_iov[1].iov_len = size;
	req->tx_iovlen = 1;
	req->tx_totallen = size;
	req->tx_type = *(u_int16_t*)server->packet;

	result = ncp_add_request(server, req);
	if (result < 0)
		goto out;

	if (wait_event_interruptible(req->wq, req->status == RQ_DONE)) {
		ncp_abort_request(server, req, -EINTR);
		result = -EINTR;
		goto out;
	}

	result = req->result;

out:
	ncp_req_put(req);

	return result;
}
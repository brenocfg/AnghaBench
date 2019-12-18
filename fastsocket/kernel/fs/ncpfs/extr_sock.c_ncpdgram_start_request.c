#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ time_out; int /*<<< orphan*/  retry_count; } ;
struct TYPE_5__ {struct ncp_request_reply* creq; } ;
struct ncp_server {TYPE_3__ m; int /*<<< orphan*/  timeout_tm; int /*<<< orphan*/  ncp_sock; int /*<<< orphan*/  timeout_retries; scalar_t__ timeout_last; TYPE_2__ rcv; } ;
struct ncp_request_reply {size_t tx_totallen; int tx_iovlen; TYPE_1__* tx_ciov; struct ncp_request_header* sign; TYPE_1__* tx_iov; } ;
struct ncp_request_header {int dummy; } ;
struct TYPE_4__ {int iov_len; struct ncp_request_header* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ncp_init_header (struct ncp_server*,struct ncp_request_reply*,struct ncp_request_header*) ; 
 int /*<<< orphan*/  ncpdgram_send (int /*<<< orphan*/ ,struct ncp_request_reply*) ; 
 size_t sign_packet (struct ncp_server*,struct ncp_request_header*,int,int /*<<< orphan*/ ,struct ncp_request_header*) ; 

__attribute__((used)) static void ncpdgram_start_request(struct ncp_server *server, struct ncp_request_reply *req)
{
	size_t signlen;
	struct ncp_request_header* h;
	
	req->tx_ciov = req->tx_iov + 1;

	h = req->tx_iov[1].iov_base;
	ncp_init_header(server, req, h);
	signlen = sign_packet(server, req->tx_iov[1].iov_base + sizeof(struct ncp_request_header) - 1, 
			req->tx_iov[1].iov_len - sizeof(struct ncp_request_header) + 1,
			cpu_to_le32(req->tx_totallen), req->sign);
	if (signlen) {
		req->tx_ciov[1].iov_base = req->sign;
		req->tx_ciov[1].iov_len = signlen;
		req->tx_iovlen += 1;
		req->tx_totallen += signlen;
	}
	server->rcv.creq = req;
	server->timeout_last = server->m.time_out;
	server->timeout_retries = server->m.retry_count;
	ncpdgram_send(server->ncp_sock, req);
	mod_timer(&server->timeout_tm, jiffies + server->m.time_out);
}
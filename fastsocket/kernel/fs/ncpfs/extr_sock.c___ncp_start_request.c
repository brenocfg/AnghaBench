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
struct ncp_server {TYPE_2__* ncp_sock; int /*<<< orphan*/  txbuf; } ;
struct ncp_request_reply {TYPE_1__* tx_iov; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {int /*<<< orphan*/  iov_base; int /*<<< orphan*/  iov_len; } ;

/* Variables and functions */
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncpdgram_start_request (struct ncp_server*,struct ncp_request_reply*) ; 
 int /*<<< orphan*/  ncptcp_start_request (struct ncp_server*,struct ncp_request_reply*) ; 

__attribute__((used)) static inline void __ncp_start_request(struct ncp_server *server, struct ncp_request_reply *req)
{
	/* we copy the data so that we do not depend on the caller
	   staying alive */
	memcpy(server->txbuf, req->tx_iov[1].iov_base, req->tx_iov[1].iov_len);
	req->tx_iov[1].iov_base = server->txbuf;

	if (server->ncp_sock->type == SOCK_STREAM)
		ncptcp_start_request(server, req);
	else
		ncpdgram_start_request(server, req);
}
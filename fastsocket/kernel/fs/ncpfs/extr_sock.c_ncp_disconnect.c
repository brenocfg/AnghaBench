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
struct ncp_server {int /*<<< orphan*/  packet_size; scalar_t__ packet; } ;
struct ncp_request_header {int task; scalar_t__ function; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCP_DEALLOC_SLOT_REQUEST ; 
 int ncp_do_request (struct ncp_server*,int,scalar_t__,int /*<<< orphan*/ ) ; 

int ncp_disconnect(struct ncp_server *server)
{
	struct ncp_request_header *h;

	h = (struct ncp_request_header *) (server->packet);
	h->type = NCP_DEALLOC_SLOT_REQUEST;
	h->task		= 2; /* see above */
	h->function	= 0;

	return ncp_do_request(server, sizeof(*h), server->packet, server->packet_size);
}
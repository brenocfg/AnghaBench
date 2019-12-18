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
struct sockaddr {int dummy; } ;
struct lsock_port {scalar_t__ type; int /*<<< orphan*/  peers; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int stream; int cred; int peerlen; int fd; int /*<<< orphan*/ * id; struct sockaddr* peer; } ;
struct lsock_peer {TYPE_1__ input; int /*<<< orphan*/  peer; struct lsock_port* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct lsock_peer*,int /*<<< orphan*/ ) ; 
 scalar_t__ LOCP_DGRAM_PRIV ; 
 scalar_t__ LOCP_STREAM_PRIV ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int accept (int,struct sockaddr*,int*) ; 
 struct lsock_peer* calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * fd_select (int,int /*<<< orphan*/ ,struct lsock_peer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct lsock_peer*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  lsock_input ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lsock_listen_input(int fd, void *udata)
{
	struct lsock_port *p = udata;
	struct lsock_peer *peer;

	if ((peer = calloc(1, sizeof(*peer))) == NULL) {
		syslog(LOG_WARNING, "%s: peer malloc failed", p->name);
		(void)close(accept(fd, NULL, NULL));
		return;
	}

	peer->port = p;

	peer->input.stream = 1;
	peer->input.cred = (p->type == LOCP_DGRAM_PRIV ||
	    p->type == LOCP_STREAM_PRIV);
	peer->input.peerlen = sizeof(peer->peer);
	peer->input.peer = (struct sockaddr *)&peer->peer;

	peer->input.fd = accept(fd, peer->input.peer, &peer->input.peerlen);
	if (peer->input.fd == -1) {
		syslog(LOG_WARNING, "%s: accept failed: %m", p->name);
		free(peer);
		return;
	}

	if ((peer->input.id = fd_select(peer->input.fd, lsock_input,
	    peer, NULL)) == NULL) {
		close(peer->input.fd);
		free(peer);
		return;
	}

	LIST_INSERT_HEAD(&p->peers, peer, link);
}
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
struct tport {int dummy; } ;
struct lsock_port {scalar_t__ str_sock; struct lsock_port* name; int /*<<< orphan*/  peers; int /*<<< orphan*/ * str_id; } ;
struct lsock_peer {int dummy; } ;

/* Variables and functions */
 struct lsock_peer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  fd_deselect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct lsock_port*) ; 
 int /*<<< orphan*/  lsock_peer_close (struct lsock_peer*) ; 
 int /*<<< orphan*/  remove (struct lsock_port*) ; 
 int /*<<< orphan*/  trans_remove_port (struct tport*) ; 

__attribute__((used)) static void
lsock_close_port(struct tport *tp)
{
	struct lsock_port *port = (struct lsock_port *)tp;
	struct lsock_peer *peer;

	if (port->str_id != NULL)
		fd_deselect(port->str_id);
	if (port->str_sock >= 0)
		(void)close(port->str_sock);
	(void)remove(port->name);

	trans_remove_port(tp);

	while ((peer = LIST_FIRST(&port->peers)) != NULL)
		lsock_peer_close(peer);

	free(port->name);
	free(port);
}
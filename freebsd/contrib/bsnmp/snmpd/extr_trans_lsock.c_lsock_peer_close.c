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
struct lsock_peer {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct lsock_peer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct lsock_peer*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  snmpd_input_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lsock_peer_close(struct lsock_peer *peer)
{

	LIST_REMOVE(peer, link);
	snmpd_input_close(&peer->input);
	free(peer);
}
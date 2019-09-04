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
struct xsocket {int dummy; } ;
struct socket {int /*<<< orphan*/  so_label; } ;
struct mbuf {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,struct xsocket*,int /*<<< orphan*/ ,struct mbuf*,struct label*) ; 
 struct label* mac_mbuf_to_label (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_label_associate_socket ; 
 int /*<<< orphan*/  sotoxsocket (struct socket*,struct xsocket*) ; 

void
mac_mbuf_label_associate_socket(struct socket *socket, struct mbuf *mbuf)
{
	struct label *label;
	struct xsocket xso;

	/* socket must be locked */

	label = mac_mbuf_to_label(mbuf);

	sotoxsocket(socket, &xso);
	MAC_PERFORM(mbuf_label_associate_socket, &xso, socket->so_label,
		    mbuf, label);
}
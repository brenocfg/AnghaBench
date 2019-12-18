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
struct sock {int /*<<< orphan*/  sk_ack_backlog; } ;
struct sctp_sock {int /*<<< orphan*/  ep; } ;
struct TYPE_2__ {struct sock* sk; } ;
struct sctp_association {TYPE_1__ base; int /*<<< orphan*/  ep; int /*<<< orphan*/  asocs; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_endpoint_add_asoc (int /*<<< orphan*/ ,struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_endpoint_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_endpoint_put (int /*<<< orphan*/ ) ; 
 struct sctp_sock* sctp_sk (struct sock*) ; 
 scalar_t__ sctp_style (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

void sctp_assoc_migrate(struct sctp_association *assoc, struct sock *newsk)
{
	struct sctp_sock *newsp = sctp_sk(newsk);
	struct sock *oldsk = assoc->base.sk;

	/* Delete the association from the old endpoint's list of
	 * associations.
	 */
	list_del_init(&assoc->asocs);

	/* Decrement the backlog value for a TCP-style socket. */
	if (sctp_style(oldsk, TCP))
		oldsk->sk_ack_backlog--;

	/* Release references to the old endpoint and the sock.  */
	sctp_endpoint_put(assoc->ep);
	sock_put(assoc->base.sk);

	/* Get a reference to the new endpoint.  */
	assoc->ep = newsp->ep;
	sctp_endpoint_hold(assoc->ep);

	/* Get a reference to the new sock.  */
	assoc->base.sk = newsk;
	sock_hold(assoc->base.sk);

	/* Add the association to the new endpoint's list of associations.  */
	sctp_endpoint_add_asoc(newsp->ep, assoc);
}
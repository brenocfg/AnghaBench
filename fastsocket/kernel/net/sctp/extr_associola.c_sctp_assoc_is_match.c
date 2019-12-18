#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ sin_port; } ;
union sctp_addr {TYPE_3__ v4; } ;
struct sctp_transport {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  port; } ;
struct TYPE_5__ {int /*<<< orphan*/  sk; TYPE_4__ bind_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  port; } ;
struct sctp_association {TYPE_1__ base; TYPE_2__ peer; } ;

/* Variables and functions */
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct sctp_transport* sctp_assoc_lookup_paddr (struct sctp_association*,union sctp_addr const*) ; 
 scalar_t__ sctp_bind_addr_match (TYPE_4__*,union sctp_addr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_sk (int /*<<< orphan*/ ) ; 

struct sctp_transport *sctp_assoc_is_match(struct sctp_association *asoc,
					   const union sctp_addr *laddr,
					   const union sctp_addr *paddr)
{
	struct sctp_transport *transport;

	if ((htons(asoc->base.bind_addr.port) == laddr->v4.sin_port) &&
	    (htons(asoc->peer.port) == paddr->v4.sin_port)) {
		transport = sctp_assoc_lookup_paddr(asoc, paddr);
		if (!transport)
			goto out;

		if (sctp_bind_addr_match(&asoc->base.bind_addr, laddr,
					 sctp_sk(asoc->base.sk)))
			goto out;
	}
	transport = NULL;

out:
	return transport;
}
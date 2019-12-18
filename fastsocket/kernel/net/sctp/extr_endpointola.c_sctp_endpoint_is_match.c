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
struct TYPE_4__ {scalar_t__ sin_port; } ;
union sctp_addr {TYPE_1__ v4; } ;
struct TYPE_6__ {int /*<<< orphan*/  port; } ;
struct TYPE_5__ {int /*<<< orphan*/  sk; TYPE_3__ bind_addr; } ;
struct sctp_endpoint {TYPE_2__ base; } ;

/* Variables and functions */
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_bind_addr_match (TYPE_3__*,union sctp_addr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_sk (int /*<<< orphan*/ ) ; 

struct sctp_endpoint *sctp_endpoint_is_match(struct sctp_endpoint *ep,
					       const union sctp_addr *laddr)
{
	struct sctp_endpoint *retval = NULL;

	if (htons(ep->base.bind_addr.port) == laddr->v4.sin_port) {
		if (sctp_bind_addr_match(&ep->base.bind_addr, laddr,
					 sctp_sk(ep->base.sk)))
			retval = ep;
	}

	return retval;
}
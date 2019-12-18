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
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct sctp_transport {int dummy; } ;
struct sctp_association {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_association_put (struct sctp_association*) ; 
 struct sctp_association* sctp_lookup_association (union sctp_addr const*,union sctp_addr const*,struct sctp_transport**) ; 

int sctp_has_association(const union sctp_addr *laddr,
			 const union sctp_addr *paddr)
{
	struct sctp_association *asoc;
	struct sctp_transport *transport;

	if ((asoc = sctp_lookup_association(laddr, paddr, &transport))) {
		sctp_association_put(asoc);
		return 1;
	}

	return 0;
}
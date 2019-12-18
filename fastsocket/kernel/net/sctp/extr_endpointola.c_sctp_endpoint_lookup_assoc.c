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
struct sctp_endpoint {int dummy; } ;
struct sctp_association {int dummy; } ;

/* Variables and functions */
 struct sctp_association* __sctp_endpoint_lookup_assoc (struct sctp_endpoint const*,union sctp_addr const*,struct sctp_transport**) ; 
 int /*<<< orphan*/  sctp_local_bh_disable () ; 
 int /*<<< orphan*/  sctp_local_bh_enable () ; 

struct sctp_association *sctp_endpoint_lookup_assoc(
	const struct sctp_endpoint *ep,
	const union sctp_addr *paddr,
	struct sctp_transport **transport)
{
	struct sctp_association *asoc;

	sctp_local_bh_disable();
	asoc = __sctp_endpoint_lookup_assoc(ep, paddr, transport);
	sctp_local_bh_enable();

	return asoc;
}
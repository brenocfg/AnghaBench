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
struct TYPE_2__ {scalar_t__ sa_family; } ;
union sctp_addr {TYPE_1__ sa; } ;
struct sctp_bind_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sctp_scope_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int SCTP_ADDR4_PEERSUPP ; 
 int SCTP_ADDR6_ALLOWED ; 
 int SCTP_ADDR6_PEERSUPP ; 
 int /*<<< orphan*/  SCTP_ADDR_SRC ; 
 int sctp_add_bind_addr (struct sctp_bind_addr*,union sctp_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sctp_copy_local_addr_list (struct sctp_bind_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sctp_in_scope (union sctp_addr*,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_is_any (int /*<<< orphan*/ *,union sctp_addr*) ; 

__attribute__((used)) static int sctp_copy_one_addr(struct sctp_bind_addr *dest,
			      union sctp_addr *addr,
			      sctp_scope_t scope, gfp_t gfp,
			      int flags)
{
	int error = 0;

	if (sctp_is_any(NULL, addr)) {
		error = sctp_copy_local_addr_list(dest, scope, gfp, flags);
	} else if (sctp_in_scope(addr, scope)) {
		/* Now that the address is in scope, check to see if
		 * the address type is supported by local sock as
		 * well as the remote peer.
		 */
		if ((((AF_INET == addr->sa.sa_family) &&
		      (flags & SCTP_ADDR4_PEERSUPP))) ||
		    (((AF_INET6 == addr->sa.sa_family) &&
		      (flags & SCTP_ADDR6_ALLOWED) &&
		      (flags & SCTP_ADDR6_PEERSUPP))))
			error = sctp_add_bind_addr(dest, addr, SCTP_ADDR_SRC,
						    gfp);
	}

	return error;
}
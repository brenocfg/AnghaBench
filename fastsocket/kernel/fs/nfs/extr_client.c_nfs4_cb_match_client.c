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
typedef  scalar_t__ u32 ;
struct sockaddr {int dummy; } ;
struct nfs_client {scalar_t__ cl_cons_state; scalar_t__ cl_minorversion; TYPE_1__* rpc_ops; int /*<<< orphan*/  cl_addr; } ;
struct TYPE_2__ {int version; } ;

/* Variables and functions */
 scalar_t__ NFS_CS_READY ; 
 scalar_t__ NFS_CS_SESSION_INITING ; 
 int /*<<< orphan*/  nfs_sockaddr_match_ipaddr (struct sockaddr const*,struct sockaddr*) ; 

bool
nfs4_cb_match_client(const struct sockaddr *addr, struct nfs_client *clp,
		     u32 minorversion)
{
	struct sockaddr *clap = (struct sockaddr *)&clp->cl_addr;

	/* Don't match clients that failed to initialise */
	if (!(clp->cl_cons_state == NFS_CS_READY ||
	    clp->cl_cons_state == NFS_CS_SESSION_INITING))
		return false;

	/* Match the version and minorversion */
	if (clp->rpc_ops->version != 4 ||
	    clp->cl_minorversion != minorversion)
		return false;

	/* Match only the IP address, not the port number */
	if (!nfs_sockaddr_match_ipaddr(addr, clap))
		return false;

	return true;
}
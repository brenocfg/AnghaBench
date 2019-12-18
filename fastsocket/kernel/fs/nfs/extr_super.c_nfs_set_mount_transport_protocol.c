#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ protocol; } ;
struct TYPE_3__ {int protocol; } ;
struct nfs_parsed_mount_data {TYPE_2__ mount_server; TYPE_1__ nfs_server; } ;

/* Variables and functions */
#define  XPRT_TRANSPORT_RDMA 130 
#define  XPRT_TRANSPORT_TCP 129 
#define  XPRT_TRANSPORT_UDP 128 
 int /*<<< orphan*/  nfs_validate_transport_protocol (struct nfs_parsed_mount_data*) ; 

__attribute__((used)) static void nfs_set_mount_transport_protocol(struct nfs_parsed_mount_data *mnt)
{
	nfs_validate_transport_protocol(mnt);

	if (mnt->mount_server.protocol == XPRT_TRANSPORT_UDP ||
	    mnt->mount_server.protocol == XPRT_TRANSPORT_TCP)
			return;
	switch (mnt->nfs_server.protocol) {
	case XPRT_TRANSPORT_UDP:
		mnt->mount_server.protocol = XPRT_TRANSPORT_UDP;
		break;
	case XPRT_TRANSPORT_TCP:
	case XPRT_TRANSPORT_RDMA:
		mnt->mount_server.protocol = XPRT_TRANSPORT_TCP;
	}
}
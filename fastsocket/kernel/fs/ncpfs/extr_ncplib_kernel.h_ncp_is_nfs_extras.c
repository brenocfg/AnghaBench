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
struct TYPE_2__ {int flags; } ;
struct ncp_server {scalar_t__* name_space; TYPE_1__ m; } ;

/* Variables and functions */
 int NCP_MOUNT_NFS_EXTRAS ; 
 scalar_t__ NW_NS_NFS ; 

__attribute__((used)) static inline int ncp_is_nfs_extras(struct ncp_server* server, unsigned int volnum) {
#ifdef CONFIG_NCPFS_NFS_NS
	return (server->m.flags & NCP_MOUNT_NFS_EXTRAS) &&
	       (server->name_space[volnum] == NW_NS_NFS);
#else
	return 0;
#endif
}
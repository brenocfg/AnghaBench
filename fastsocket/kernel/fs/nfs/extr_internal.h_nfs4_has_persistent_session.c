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
struct nfs_client {TYPE_1__* cl_session; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int SESSION4_PERSIST ; 
 scalar_t__ nfs4_has_session (struct nfs_client const*) ; 

__attribute__((used)) static inline int nfs4_has_persistent_session(const struct nfs_client *clp)
{
#ifdef CONFIG_NFS_V4_1
	if (nfs4_has_session(clp))
		return (clp->cl_session->flags & SESSION4_PERSIST);
#endif /* CONFIG_NFS_V4_1 */
	return 0;
}
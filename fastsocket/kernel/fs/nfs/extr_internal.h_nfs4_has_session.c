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
struct nfs_client {scalar_t__ cl_session; } ;

/* Variables and functions */

__attribute__((used)) static inline int nfs4_has_session(const struct nfs_client *clp)
{
#ifdef CONFIG_NFS_V4_1
	if (clp->cl_session)
		return 1;
#endif /* CONFIG_NFS_V4_1 */ 
	return 0;
}
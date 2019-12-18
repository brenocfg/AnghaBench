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
typedef  int u32 ;
struct nfs_access_entry {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAY_EXEC ; 
 int /*<<< orphan*/  MAY_READ ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 int NFS4_ACCESS_DELETE ; 
 int NFS4_ACCESS_EXECUTE ; 
 int NFS4_ACCESS_EXTEND ; 
 int NFS4_ACCESS_LOOKUP ; 
 int NFS4_ACCESS_MODIFY ; 
 int NFS4_ACCESS_READ ; 

void nfs_access_set_mask(struct nfs_access_entry *entry, u32 access_result)
{
	entry->mask = 0;
	if (access_result & NFS4_ACCESS_READ)
		entry->mask |= MAY_READ;
	if (access_result &
	    (NFS4_ACCESS_MODIFY | NFS4_ACCESS_EXTEND | NFS4_ACCESS_DELETE))
		entry->mask |= MAY_WRITE;
	if (access_result & (NFS4_ACCESS_LOOKUP|NFS4_ACCESS_EXECUTE))
		entry->mask |= MAY_EXEC;
}
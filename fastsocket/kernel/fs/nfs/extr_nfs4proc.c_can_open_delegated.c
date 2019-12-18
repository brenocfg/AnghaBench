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
struct nfs_delegation {int type; int /*<<< orphan*/  flags; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_DELEGATION_NEED_RECLAIM ; 
 int /*<<< orphan*/  NFS_DELEGATION_RETURNING ; 
 int /*<<< orphan*/  nfs_mark_delegation_referenced (struct nfs_delegation*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int can_open_delegated(struct nfs_delegation *delegation, fmode_t fmode)
{
	if (delegation == NULL)
		return 0;
	if ((delegation->type & fmode) != fmode)
		return 0;
	if (test_bit(NFS_DELEGATION_NEED_RECLAIM, &delegation->flags))
		return 0;
	if (test_bit(NFS_DELEGATION_RETURNING, &delegation->flags))
		return 0;
	nfs_mark_delegation_referenced(delegation);
	return 1;
}
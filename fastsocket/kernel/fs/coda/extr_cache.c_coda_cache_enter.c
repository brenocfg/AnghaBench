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
struct inode {int dummy; } ;
struct coda_inode_info {scalar_t__ c_uid; int c_cached_perm; int /*<<< orphan*/  c_cached_epoch; } ;

/* Variables and functions */
 struct coda_inode_info* ITOC (struct inode*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ current_fsuid () ; 
 int /*<<< orphan*/  permission_epoch ; 

void coda_cache_enter(struct inode *inode, int mask)
{
	struct coda_inode_info *cii = ITOC(inode);

	cii->c_cached_epoch = atomic_read(&permission_epoch);
	if (cii->c_uid != current_fsuid()) {
		cii->c_uid = current_fsuid();
                cii->c_cached_perm = mask;
        } else
                cii->c_cached_perm |= mask;
}
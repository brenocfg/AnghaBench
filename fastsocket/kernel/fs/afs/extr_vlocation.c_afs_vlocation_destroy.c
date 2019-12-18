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
struct afs_vlocation {int /*<<< orphan*/  cell; int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,struct afs_vlocation*) ; 
 int /*<<< orphan*/  afs_put_cell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_relinquish_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct afs_vlocation*) ; 

__attribute__((used)) static void afs_vlocation_destroy(struct afs_vlocation *vl)
{
	_enter("%p", vl);

#ifdef CONFIG_AFS_FSCACHE
	fscache_relinquish_cookie(vl->cache, 0);
#endif
	afs_put_cell(vl->cell);
	kfree(vl);
}
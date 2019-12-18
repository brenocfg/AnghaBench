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
typedef  int /*<<< orphan*/  u32 ;
struct pnfs_layoutdriver_type {int dummy; } ;

/* Variables and functions */
 struct pnfs_layoutdriver_type* find_pnfs_driver_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_spinlock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pnfs_layoutdriver_type *
find_pnfs_driver(u32 id)
{
	struct pnfs_layoutdriver_type *local;

	spin_lock(&pnfs_spinlock);
	local = find_pnfs_driver_locked(id);
	spin_unlock(&pnfs_spinlock);
	return local;
}
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
struct xfrm_mgr {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_km_list ; 
 int /*<<< orphan*/  xfrm_km_lock ; 

int xfrm_register_km(struct xfrm_mgr *km)
{
	write_lock_bh(&xfrm_km_lock);
	list_add_tail(&km->list, &xfrm_km_list);
	write_unlock_bh(&xfrm_km_lock);
	return 0;
}
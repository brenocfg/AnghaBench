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

/* Variables and functions */
 int /*<<< orphan*/  __rds_iw_destroy_conns (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iw_nodev_conns ; 
 int /*<<< orphan*/  iw_nodev_conns_lock ; 

__attribute__((used)) static inline void rds_iw_destroy_nodev_conns(void)
{
	__rds_iw_destroy_conns(&iw_nodev_conns, &iw_nodev_conns_lock);
}
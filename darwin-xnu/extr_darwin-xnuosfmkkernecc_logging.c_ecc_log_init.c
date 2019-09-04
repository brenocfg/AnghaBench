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
 int /*<<< orphan*/  OSMemoryBarrier () ; 
 int /*<<< orphan*/  ecc_data_lock ; 
 int /*<<< orphan*/  ecc_data_lock_group ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_spin_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ecc_log_init()
{
	ecc_data_lock_group = lck_grp_alloc_init("ecc-data", NULL);
	lck_spin_init(&ecc_data_lock, ecc_data_lock_group, NULL);
	OSMemoryBarrier();
}
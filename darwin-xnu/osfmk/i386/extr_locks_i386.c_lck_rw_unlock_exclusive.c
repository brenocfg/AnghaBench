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
typedef  scalar_t__ lck_rw_type_t ;
typedef  int /*<<< orphan*/  lck_rw_t ;

/* Variables and functions */
 scalar_t__ LCK_RW_TYPE_EXCLUSIVE ; 
 scalar_t__ lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 

void
lck_rw_unlock_exclusive(
	lck_rw_t	*lck)
{
	lck_rw_type_t	ret;

	ret = lck_rw_done(lck);

	if (ret != LCK_RW_TYPE_EXCLUSIVE)
		panic("lck_rw_unlock_exclusive(): lock held in mode: %d\n", ret);
}
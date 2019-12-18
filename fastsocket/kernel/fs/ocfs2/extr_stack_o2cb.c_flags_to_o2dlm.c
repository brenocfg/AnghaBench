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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DLM_LKF_CANCEL ; 
 int /*<<< orphan*/  DLM_LKF_CONVERT ; 
 int /*<<< orphan*/  DLM_LKF_FORCEUNLOCK ; 
 int /*<<< orphan*/  DLM_LKF_IVVALBLK ; 
 int /*<<< orphan*/  DLM_LKF_LOCAL ; 
 int /*<<< orphan*/  DLM_LKF_NOQUEUE ; 
 int /*<<< orphan*/  DLM_LKF_ORPHAN ; 
 int /*<<< orphan*/  DLM_LKF_TIMEOUT ; 
 int /*<<< orphan*/  DLM_LKF_VALBLK ; 
 int /*<<< orphan*/  LKM_CANCEL ; 
 int /*<<< orphan*/  LKM_CONVERT ; 
 int /*<<< orphan*/  LKM_FORCE ; 
 int /*<<< orphan*/  LKM_INVVALBLK ; 
 int /*<<< orphan*/  LKM_LOCAL ; 
 int /*<<< orphan*/  LKM_NOQUEUE ; 
 int /*<<< orphan*/  LKM_ORPHAN ; 
 int /*<<< orphan*/  LKM_TIMEOUT ; 
 int /*<<< orphan*/  LKM_VALBLK ; 
 int /*<<< orphan*/  map_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flags_to_o2dlm(u32 flags)
{
	int o2dlm_flags = 0;

	map_flag(DLM_LKF_NOQUEUE, LKM_NOQUEUE);
	map_flag(DLM_LKF_CANCEL, LKM_CANCEL);
	map_flag(DLM_LKF_CONVERT, LKM_CONVERT);
	map_flag(DLM_LKF_VALBLK, LKM_VALBLK);
	map_flag(DLM_LKF_IVVALBLK, LKM_INVVALBLK);
	map_flag(DLM_LKF_ORPHAN, LKM_ORPHAN);
	map_flag(DLM_LKF_FORCEUNLOCK, LKM_FORCE);
	map_flag(DLM_LKF_TIMEOUT, LKM_TIMEOUT);
	map_flag(DLM_LKF_LOCAL, LKM_LOCAL);

	/* map_flag() should have cleared every flag passed in */
	BUG_ON(flags != 0);

	return o2dlm_flags;
}
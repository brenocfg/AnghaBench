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
 int /*<<< orphan*/  GUC_ACTION_LOCAL ; 
 int /*<<< orphan*/  PGC_SUSET ; 
 int /*<<< orphan*/  PGC_S_SESSION ; 
 int /*<<< orphan*/  PGC_USERSET ; 
 int /*<<< orphan*/  set_config_option (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ superuser () ; 

void
SetLocalMultiShardModifyModeToSequential()
{
	set_config_option("citus.multi_shard_modify_mode", "sequential",
					  (superuser() ? PGC_SUSET : PGC_USERSET), PGC_S_SESSION,
					  GUC_ACTION_LOCAL, true, 0, false);
}
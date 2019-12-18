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
struct se_portal_group {int dummy; } ;
struct se_lun {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  core_clear_lun_from_tpg (struct se_lun*,struct se_portal_group*) ; 
 int /*<<< orphan*/  transport_clear_lun_from_sessions (struct se_lun*) ; 

__attribute__((used)) static void core_tpg_shutdown_lun(
	struct se_portal_group *tpg,
	struct se_lun *lun)
{
	core_clear_lun_from_tpg(lun, tpg);
	transport_clear_lun_from_sessions(lun);
}
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
struct se_lun {int /*<<< orphan*/  lun_sep; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  core_alua_store_tg_pt_gp_info (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static ssize_t target_fabric_port_store_attr_alua_tg_pt_gp(
	struct se_lun *lun,
	const char *page,
	size_t count)
{
	if (!lun || !lun->lun_sep)
		return -ENODEV;

	return core_alua_store_tg_pt_gp_info(lun->lun_sep, page, count);
}
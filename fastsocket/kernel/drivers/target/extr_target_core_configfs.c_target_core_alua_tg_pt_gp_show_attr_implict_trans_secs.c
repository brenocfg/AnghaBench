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
struct t10_alua_tg_pt_gp {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  core_alua_show_implict_trans_secs (struct t10_alua_tg_pt_gp*,char*) ; 

__attribute__((used)) static ssize_t target_core_alua_tg_pt_gp_show_attr_implict_trans_secs(
	struct t10_alua_tg_pt_gp *tg_pt_gp,
	char *page)
{
	return core_alua_show_implict_trans_secs(tg_pt_gp, page);
}
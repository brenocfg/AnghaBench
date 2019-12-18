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
struct t10_alua_tg_pt_gp {int /*<<< orphan*/  tg_pt_gp_alua_access_status; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* core_alua_dump_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t target_core_alua_tg_pt_gp_show_attr_alua_access_status(
	struct t10_alua_tg_pt_gp *tg_pt_gp,
	char *page)
{
	return sprintf(page, "%s\n",
		core_alua_dump_status(tg_pt_gp->tg_pt_gp_alua_access_status));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct netlbl_domhsh_walk_arg {scalar_t__ doi; int /*<<< orphan*/  audit_info; } ;
struct TYPE_4__ {TYPE_1__* cipsov4; } ;
struct netlbl_dom_map {scalar_t__ type; TYPE_2__ type_def; } ;
struct TYPE_3__ {scalar_t__ doi; } ;

/* Variables and functions */
 scalar_t__ NETLBL_NLTYPE_CIPSOV4 ; 
 int netlbl_domhsh_remove_entry (struct netlbl_dom_map*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netlbl_cipsov4_remove_cb(struct netlbl_dom_map *entry, void *arg)
{
	struct netlbl_domhsh_walk_arg *cb_arg = arg;

	if (entry->type == NETLBL_NLTYPE_CIPSOV4 &&
	    entry->type_def.cipsov4->doi == cb_arg->doi)
		return netlbl_domhsh_remove_entry(entry, cb_arg->audit_info);

	return 0;
}
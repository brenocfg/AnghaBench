#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct variable_list {int /*<<< orphan*/  vars; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  fb_ops; } ;
struct available_var_finder {int nvls; TYPE_1__ pf; scalar_t__ child; struct variable_list* vls; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int DIE_FIND_CB_CONTINUE ; 
 int DIE_FIND_CB_SIBLING ; 
 int DW_TAG_formal_parameter ; 
 int DW_TAG_variable ; 
 int MAX_VAR_LEN ; 
 int convert_variable_location (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int die_get_varname (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ dwarf_haspc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwarf_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug2 (char*,char*) ; 
 int /*<<< orphan*/  strlist__add (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int collect_variables_cb(Dwarf_Die *die_mem, void *data)
{
	struct available_var_finder *af = data;
	struct variable_list *vl;
	char buf[MAX_VAR_LEN];
	int tag, ret;

	vl = &af->vls[af->nvls - 1];

	tag = dwarf_tag(die_mem);
	if (tag == DW_TAG_formal_parameter ||
	    tag == DW_TAG_variable) {
		ret = convert_variable_location(die_mem, af->pf.addr,
						af->pf.fb_ops, NULL);
		if (ret == 0) {
			ret = die_get_varname(die_mem, buf, MAX_VAR_LEN);
			pr_debug2("Add new var: %s\n", buf);
			if (ret > 0)
				strlist__add(vl->vars, buf);
		}
	}

	if (af->child && dwarf_haspc(die_mem, af->pf.addr))
		return DIE_FIND_CB_CONTINUE;
	else
		return DIE_FIND_CB_SIBLING;
}
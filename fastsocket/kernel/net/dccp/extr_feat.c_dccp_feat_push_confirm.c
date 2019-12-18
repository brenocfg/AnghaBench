#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct list_head {int dummy; } ;
struct TYPE_3__ {scalar_t__ nn; } ;
struct dccp_feat_entry {int needs_confirm; scalar_t__ needs_mandatory; TYPE_1__ val; int /*<<< orphan*/  empty_confirm; int /*<<< orphan*/  state; void* is_local; void* feat_num; } ;
typedef  TYPE_1__ dccp_feat_val ;

/* Variables and functions */
 int DCCP_RESET_CODE_TOO_BUSY ; 
 int /*<<< orphan*/  FEAT_STABLE ; 
 struct dccp_feat_entry* dccp_feat_entry_new (struct list_head*,void*,void*) ; 

__attribute__((used)) static int dccp_feat_push_confirm(struct list_head *fn_list, u8 feat, u8 local,
				  dccp_feat_val *fval)
{
	struct dccp_feat_entry *new = dccp_feat_entry_new(fn_list, feat, local);

	if (new == NULL)
		return DCCP_RESET_CODE_TOO_BUSY;

	new->feat_num	     = feat;
	new->is_local	     = local;
	new->state	     = FEAT_STABLE;	/* transition in 6.6.2 */
	new->needs_confirm   = 1;
	new->empty_confirm   = (fval == NULL);
	new->val.nn	     = 0;		/* zeroes the whole structure */
	if (!new->empty_confirm)
		new->val     = *fval;
	new->needs_mandatory = 0;

	return 0;
}
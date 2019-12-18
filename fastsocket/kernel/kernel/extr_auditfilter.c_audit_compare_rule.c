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
struct audit_krule {scalar_t__ flags; scalar_t__ listnr; scalar_t__ action; int field_count; scalar_t__* mask; TYPE_1__* fields; int /*<<< orphan*/  filterkey; int /*<<< orphan*/  tree; int /*<<< orphan*/  watch; } ;
struct TYPE_2__ {int type; scalar_t__ op; int /*<<< orphan*/  val; int /*<<< orphan*/  lsm_str; } ;

/* Variables and functions */
 int AUDIT_BITMASK_SIZE ; 
#define  AUDIT_DIR 140 
#define  AUDIT_FILTERKEY 139 
#define  AUDIT_OBJ_LEV_HIGH 138 
#define  AUDIT_OBJ_LEV_LOW 137 
#define  AUDIT_OBJ_ROLE 136 
#define  AUDIT_OBJ_TYPE 135 
#define  AUDIT_OBJ_USER 134 
#define  AUDIT_SUBJ_CLR 133 
#define  AUDIT_SUBJ_ROLE 132 
#define  AUDIT_SUBJ_SEN 131 
#define  AUDIT_SUBJ_TYPE 130 
#define  AUDIT_SUBJ_USER 129 
#define  AUDIT_WATCH 128 
 int /*<<< orphan*/  audit_tree_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_watch_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audit_compare_rule(struct audit_krule *a, struct audit_krule *b)
{
	int i;

	if (a->flags != b->flags ||
	    a->listnr != b->listnr ||
	    a->action != b->action ||
	    a->field_count != b->field_count)
		return 1;

	for (i = 0; i < a->field_count; i++) {
		if (a->fields[i].type != b->fields[i].type ||
		    a->fields[i].op != b->fields[i].op)
			return 1;

		switch(a->fields[i].type) {
		case AUDIT_SUBJ_USER:
		case AUDIT_SUBJ_ROLE:
		case AUDIT_SUBJ_TYPE:
		case AUDIT_SUBJ_SEN:
		case AUDIT_SUBJ_CLR:
		case AUDIT_OBJ_USER:
		case AUDIT_OBJ_ROLE:
		case AUDIT_OBJ_TYPE:
		case AUDIT_OBJ_LEV_LOW:
		case AUDIT_OBJ_LEV_HIGH:
			if (strcmp(a->fields[i].lsm_str, b->fields[i].lsm_str))
				return 1;
			break;
		case AUDIT_WATCH:
			if (strcmp(audit_watch_path(a->watch),
				   audit_watch_path(b->watch)))
				return 1;
			break;
		case AUDIT_DIR:
			if (strcmp(audit_tree_path(a->tree),
				   audit_tree_path(b->tree)))
				return 1;
			break;
		case AUDIT_FILTERKEY:
			/* both filterkeys exist based on above type compare */
			if (strcmp(a->filterkey, b->filterkey))
				return 1;
			break;
		default:
			if (a->fields[i].val != b->fields[i].val)
				return 1;
		}
	}

	for (i = 0; i < AUDIT_BITMASK_SIZE; i++)
		if (a->mask[i] != b->mask[i])
			return 1;

	return 0;
}
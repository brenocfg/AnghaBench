#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct user_datum {int /*<<< orphan*/  value; } ;
struct type_datum {int /*<<< orphan*/  value; } ;
struct TYPE_11__ {int /*<<< orphan*/  type; int /*<<< orphan*/  role; int /*<<< orphan*/  user; } ;
struct selinux_audit_rule {TYPE_5__ au_ctxt; int /*<<< orphan*/  au_seqno; } ;
struct role_datum {int /*<<< orphan*/  value; } ;
struct TYPE_9__ {int /*<<< orphan*/  table; } ;
struct TYPE_8__ {int /*<<< orphan*/  table; } ;
struct TYPE_7__ {int /*<<< orphan*/  table; } ;
struct TYPE_10__ {TYPE_3__ p_types; TYPE_2__ p_roles; TYPE_1__ p_users; } ;

/* Variables and functions */
#define  AUDIT_OBJ_LEV_HIGH 137 
#define  AUDIT_OBJ_LEV_LOW 136 
#define  AUDIT_OBJ_ROLE 135 
#define  AUDIT_OBJ_TYPE 134 
#define  AUDIT_OBJ_USER 133 
#define  AUDIT_SUBJ_CLR 132 
#define  AUDIT_SUBJ_ROLE 131 
#define  AUDIT_SUBJ_SEN 130 
#define  AUDIT_SUBJ_TYPE 129 
#define  AUDIT_SUBJ_USER 128 
 int Audit_equal ; 
 int Audit_not_equal ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  context_init (TYPE_5__*) ; 
 void* hashtab_search (int /*<<< orphan*/ ,char*) ; 
 struct selinux_audit_rule* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latest_granting ; 
 int mls_from_string (char*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_rwlock ; 
 TYPE_4__ policydb ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_audit_rule_free (struct selinux_audit_rule*) ; 
 int /*<<< orphan*/  ss_initialized ; 
 int /*<<< orphan*/  strchr (char*,char) ; 

int selinux_audit_rule_init(u32 field, u32 op, char *rulestr, void **vrule)
{
	struct selinux_audit_rule *tmprule;
	struct role_datum *roledatum;
	struct type_datum *typedatum;
	struct user_datum *userdatum;
	struct selinux_audit_rule **rule = (struct selinux_audit_rule **)vrule;
	int rc = 0;

	*rule = NULL;

	if (!ss_initialized)
		return -EOPNOTSUPP;

	switch (field) {
	case AUDIT_SUBJ_USER:
	case AUDIT_SUBJ_ROLE:
	case AUDIT_SUBJ_TYPE:
	case AUDIT_OBJ_USER:
	case AUDIT_OBJ_ROLE:
	case AUDIT_OBJ_TYPE:
		/* only 'equals' and 'not equals' fit user, role, and type */
		if (op != Audit_equal && op != Audit_not_equal)
			return -EINVAL;
		break;
	case AUDIT_SUBJ_SEN:
	case AUDIT_SUBJ_CLR:
	case AUDIT_OBJ_LEV_LOW:
	case AUDIT_OBJ_LEV_HIGH:
		/* we do not allow a range, indicated by the presense of '-' */
		if (strchr(rulestr, '-'))
			return -EINVAL;
		break;
	default:
		/* only the above fields are valid */
		return -EINVAL;
	}

	tmprule = kzalloc(sizeof(struct selinux_audit_rule), GFP_KERNEL);
	if (!tmprule)
		return -ENOMEM;

	context_init(&tmprule->au_ctxt);

	read_lock(&policy_rwlock);

	tmprule->au_seqno = latest_granting;

	switch (field) {
	case AUDIT_SUBJ_USER:
	case AUDIT_OBJ_USER:
		userdatum = hashtab_search(policydb.p_users.table, rulestr);
		if (!userdatum)
			rc = -EINVAL;
		else
			tmprule->au_ctxt.user = userdatum->value;
		break;
	case AUDIT_SUBJ_ROLE:
	case AUDIT_OBJ_ROLE:
		roledatum = hashtab_search(policydb.p_roles.table, rulestr);
		if (!roledatum)
			rc = -EINVAL;
		else
			tmprule->au_ctxt.role = roledatum->value;
		break;
	case AUDIT_SUBJ_TYPE:
	case AUDIT_OBJ_TYPE:
		typedatum = hashtab_search(policydb.p_types.table, rulestr);
		if (!typedatum)
			rc = -EINVAL;
		else
			tmprule->au_ctxt.type = typedatum->value;
		break;
	case AUDIT_SUBJ_SEN:
	case AUDIT_SUBJ_CLR:
	case AUDIT_OBJ_LEV_LOW:
	case AUDIT_OBJ_LEV_HIGH:
		rc = mls_from_string(rulestr, &tmprule->au_ctxt, GFP_ATOMIC);
		break;
	}

	read_unlock(&policy_rwlock);

	if (rc) {
		selinux_audit_rule_free(tmprule);
		tmprule = NULL;
	}

	*rule = tmprule;

	return rc;
}
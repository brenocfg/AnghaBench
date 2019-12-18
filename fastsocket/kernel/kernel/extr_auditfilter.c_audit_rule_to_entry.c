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
typedef  int u32 ;
struct audit_rule {int field_count; int* fields; int* values; } ;
struct audit_field {scalar_t__ op; int type; int val; } ;
struct TYPE_4__ {int vers_ops; TYPE_1__* inode_f; struct audit_field* arch_f; struct audit_field* fields; } ;
struct audit_entry {TYPE_2__ rule; } ;
struct TYPE_3__ {scalar_t__ op; } ;

/* Variables and functions */
#define  AUDIT_ARCH 152 
#define  AUDIT_ARG0 151 
#define  AUDIT_ARG1 150 
#define  AUDIT_ARG2 149 
#define  AUDIT_ARG3 148 
#define  AUDIT_DEVMAJOR 147 
#define  AUDIT_DEVMINOR 146 
#define  AUDIT_EGID 145 
#define  AUDIT_EUID 144 
#define  AUDIT_EXIT 143 
#define  AUDIT_FILETYPE 142 
#define  AUDIT_FSGID 141 
#define  AUDIT_FSUID 140 
#define  AUDIT_GID 139 
#define  AUDIT_INODE 138 
#define  AUDIT_LOGINUID 137 
#define  AUDIT_MSGTYPE 136 
 int AUDIT_NEGATE ; 
 int AUDIT_OPERATORS ; 
#define  AUDIT_PERM 135 
#define  AUDIT_PERS 134 
#define  AUDIT_PID 133 
#define  AUDIT_PPID 132 
#define  AUDIT_SGID 131 
#define  AUDIT_SUCCESS 130 
#define  AUDIT_SUID 129 
#define  AUDIT_UID 128 
 scalar_t__ Audit_bad ; 
 scalar_t__ Audit_bitmask ; 
 scalar_t__ Audit_bittest ; 
 scalar_t__ Audit_equal ; 
 scalar_t__ Audit_not_equal ; 
 int EINVAL ; 
 struct audit_entry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct audit_entry*) ; 
 int S_IFMT ; 
 int /*<<< orphan*/  audit_free_rule (struct audit_entry*) ; 
 struct audit_entry* audit_to_entry_common (struct audit_rule*) ; 
 int audit_to_inode (TYPE_2__*,struct audit_field*) ; 
 scalar_t__ audit_to_op (int) ; 

__attribute__((used)) static struct audit_entry *audit_rule_to_entry(struct audit_rule *rule)
{
	struct audit_entry *entry;
	int err = 0;
	int i;

	entry = audit_to_entry_common(rule);
	if (IS_ERR(entry))
		goto exit_nofree;

	for (i = 0; i < rule->field_count; i++) {
		struct audit_field *f = &entry->rule.fields[i];
		u32 n;

		n = rule->fields[i] & (AUDIT_NEGATE|AUDIT_OPERATORS);

		/* Support for legacy operators where
		 * AUDIT_NEGATE bit signifies != and otherwise assumes == */
		if (n & AUDIT_NEGATE)
			f->op = Audit_not_equal;
		else if (!n)
			f->op = Audit_equal;
		else
			f->op = audit_to_op(n);

		entry->rule.vers_ops = (n & AUDIT_OPERATORS) ? 2 : 1;

		f->type = rule->fields[i] & ~(AUDIT_NEGATE|AUDIT_OPERATORS);
		f->val = rule->values[i];

		err = -EINVAL;
		if (f->op == Audit_bad)
			goto exit_free;

		switch(f->type) {
		default:
			goto exit_free;
		case AUDIT_PID:
		case AUDIT_UID:
		case AUDIT_EUID:
		case AUDIT_SUID:
		case AUDIT_FSUID:
		case AUDIT_GID:
		case AUDIT_EGID:
		case AUDIT_SGID:
		case AUDIT_FSGID:
		case AUDIT_LOGINUID:
		case AUDIT_PERS:
		case AUDIT_MSGTYPE:
		case AUDIT_PPID:
		case AUDIT_DEVMAJOR:
		case AUDIT_DEVMINOR:
		case AUDIT_EXIT:
		case AUDIT_SUCCESS:
			/* bit ops are only useful on syscall args */
			if (f->op == Audit_bitmask || f->op == Audit_bittest)
				goto exit_free;
			break;
		case AUDIT_ARG0:
		case AUDIT_ARG1:
		case AUDIT_ARG2:
		case AUDIT_ARG3:
			break;
		/* arch is only allowed to be = or != */
		case AUDIT_ARCH:
			if (f->op != Audit_not_equal && f->op != Audit_equal)
				goto exit_free;
			entry->rule.arch_f = f;
			break;
		case AUDIT_PERM:
			if (f->val & ~15)
				goto exit_free;
			break;
		case AUDIT_FILETYPE:
			if (f->val & ~S_IFMT)
				goto exit_free;
			break;
		case AUDIT_INODE:
			err = audit_to_inode(&entry->rule, f);
			if (err)
				goto exit_free;
			break;
		}
	}

	if (entry->rule.inode_f && entry->rule.inode_f->op == Audit_not_equal)
		entry->rule.inode_f = NULL;

exit_nofree:
	return entry;

exit_free:
	audit_free_rule(entry);
	return ERR_PTR(err);
}
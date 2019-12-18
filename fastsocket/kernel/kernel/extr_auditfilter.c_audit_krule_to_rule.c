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
struct audit_rule {int flags; int field_count; int /*<<< orphan*/ * mask; int /*<<< orphan*/ * fields; int /*<<< orphan*/ * values; int /*<<< orphan*/  action; } ;
struct audit_krule {int flags; int listnr; int field_count; int vers_ops; int /*<<< orphan*/ * mask; TYPE_1__* fields; int /*<<< orphan*/  action; } ;
struct TYPE_2__ {size_t op; int /*<<< orphan*/  type; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int AUDIT_BITMASK_SIZE ; 
 int /*<<< orphan*/  AUDIT_NEGATE ; 
 size_t Audit_not_equal ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * audit_ops ; 
 struct audit_rule* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct audit_rule *audit_krule_to_rule(struct audit_krule *krule)
{
	struct audit_rule *rule;
	int i;

	rule = kzalloc(sizeof(*rule), GFP_KERNEL);
	if (unlikely(!rule))
		return NULL;

	rule->flags = krule->flags | krule->listnr;
	rule->action = krule->action;
	rule->field_count = krule->field_count;
	for (i = 0; i < rule->field_count; i++) {
		rule->values[i] = krule->fields[i].val;
		rule->fields[i] = krule->fields[i].type;

		if (krule->vers_ops == 1) {
			if (krule->fields[i].op == Audit_not_equal)
				rule->fields[i] |= AUDIT_NEGATE;
		} else {
			rule->fields[i] |= audit_ops[krule->fields[i].op];
		}
	}
	for (i = 0; i < AUDIT_BITMASK_SIZE; i++) rule->mask[i] = krule->mask[i];

	return rule;
}
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
struct audit_krule {int field_count; struct audit_field* filterkey; struct audit_field* fields; scalar_t__ watch; } ;
struct audit_field {int /*<<< orphan*/  lsm_rule; struct audit_field* lsm_str; struct audit_krule rule; } ;
struct audit_entry {int /*<<< orphan*/  lsm_rule; struct audit_entry* lsm_str; struct audit_krule rule; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_put_watch (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct audit_field*) ; 
 int /*<<< orphan*/  security_audit_rule_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void audit_free_rule(struct audit_entry *e)
{
	int i;
	struct audit_krule *erule = &e->rule;
	/* some rules don't have associated watches */
	if (erule->watch)
		audit_put_watch(erule->watch);
	if (erule->fields)
		for (i = 0; i < erule->field_count; i++) {
			struct audit_field *f = &erule->fields[i];
			kfree(f->lsm_str);
			security_audit_rule_free(f->lsm_rule);
		}
	kfree(erule->fields);
	kfree(erule->filterkey);
	kfree(e);
}
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
struct ima_measure_rule_entry {int /*<<< orphan*/  list; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_INTEGRITY_STATUS ; 
 int EACCES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ima_measure ; 
 int /*<<< orphan*/  ima_measure_mutex ; 
 int ima_parse_rule (char*,struct ima_measure_rule_entry*) ; 
 int /*<<< orphan*/  integrity_audit_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char*,int,int) ; 
 int /*<<< orphan*/  kfree (struct ima_measure_rule_entry*) ; 
 struct ima_measure_rule_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  measure_default_rules ; 
 int /*<<< orphan*/  measure_policy_rules ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 

ssize_t ima_parse_add_rule(char *rule)
{
	const char *op = "update_policy";
	char *p;
	struct ima_measure_rule_entry *entry;
	ssize_t result, len;
	int audit_info = 0;

	/* Prevent installed policy from changing */
	if (ima_measure != &measure_default_rules) {
		integrity_audit_msg(AUDIT_INTEGRITY_STATUS, NULL,
				    NULL, op, "already exists",
				    -EACCES, audit_info);
		return -EACCES;
	}

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		integrity_audit_msg(AUDIT_INTEGRITY_STATUS, NULL,
				    NULL, op, "-ENOMEM", -ENOMEM, audit_info);
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&entry->list);

	p = strsep(&rule, "\n");
	len = strlen(p) + 1;

	if (*p == '#') {
		kfree(entry);
		return len;
	}

	result = ima_parse_rule(p, entry);
	if (result) {
		kfree(entry);
		integrity_audit_msg(AUDIT_INTEGRITY_STATUS, NULL,
				    NULL, op, "invalid policy", result,
				    audit_info);
		return result;
	}

	mutex_lock(&ima_measure_mutex);
	list_add_tail(&entry->list, &measure_policy_rules);
	mutex_unlock(&ima_measure_mutex);

	return len;
}
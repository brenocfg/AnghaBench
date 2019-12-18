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
struct inode {int dummy; } ;
struct ima_template_entry {int template_len; int /*<<< orphan*/  template_name; int /*<<< orphan*/  digest; int /*<<< orphan*/  template; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_INTEGRITY_PCR ; 
 int /*<<< orphan*/  IMA_TEMPLATE_NAME ; 
 int ima_add_template_entry (struct ima_template_entry*,int,char const*,struct inode*) ; 
 int ima_calc_template_hash (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integrity_audit_msg (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,char const*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ima_store_template(struct ima_template_entry *entry,
		       int violation, struct inode *inode)
{
	const char *op = "add_template_measure";
	const char *audit_cause = "hashing_error";
	int result;

	memset(entry->digest, 0, sizeof(entry->digest));
	entry->template_name = IMA_TEMPLATE_NAME;
	entry->template_len = sizeof(entry->template);

	if (!violation) {
		result = ima_calc_template_hash(entry->template_len,
						&entry->template,
						entry->digest);
		if (result < 0) {
			integrity_audit_msg(AUDIT_INTEGRITY_PCR, inode,
					    entry->template_name, op,
					    audit_cause, result, 0);
			return result;
		}
	}
	result = ima_add_template_entry(entry, violation, op, inode);
	return result;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  file_name; } ;
struct ima_template_entry {TYPE_1__ template; int /*<<< orphan*/  digest; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_INTEGRITY_PCR ; 
 int IMA_DIGEST_SIZE ; 
 int ima_add_digest_entry (struct ima_template_entry*) ; 
 int /*<<< orphan*/  ima_extend_list_mutex ; 
 scalar_t__ ima_lookup_digest_entry (int /*<<< orphan*/ *) ; 
 int ima_pcr_extend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  integrity_audit_msg (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,char const*,char const*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ima_add_template_entry(struct ima_template_entry *entry, int violation,
			   const char *op, struct inode *inode)
{
	u8 digest[IMA_DIGEST_SIZE];
	const char *audit_cause = "hash_added";
	int audit_info = 1;
	int result = 0;

	mutex_lock(&ima_extend_list_mutex);
	if (!violation) {
		memcpy(digest, entry->digest, sizeof digest);
		if (ima_lookup_digest_entry(digest)) {
			audit_cause = "hash_exists";
			goto out;
		}
	}

	result = ima_add_digest_entry(entry);
	if (result < 0) {
		audit_cause = "ENOMEM";
		audit_info = 0;
		goto out;
	}

	if (violation)		/* invalidate pcr */
		memset(digest, 0xff, sizeof digest);

	result = ima_pcr_extend(digest);
	if (result != 0) {
		audit_cause = "TPM error";
		audit_info = 0;
	}
out:
	mutex_unlock(&ima_extend_list_mutex);
	integrity_audit_msg(AUDIT_INTEGRITY_PCR, inode,
			    entry->template.file_name,
			    op, audit_cause, result, audit_info);
	return result;
}
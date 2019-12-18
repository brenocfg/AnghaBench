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
struct inode {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  file_name; } ;
struct ima_template_entry {TYPE_1__ template; } ;
struct TYPE_4__ {int /*<<< orphan*/  violations; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_INTEGRITY_PCR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IMA_EVENT_NAME_LEN_MAX ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 TYPE_2__ ima_htable ; 
 int ima_store_template (struct ima_template_entry*,int,struct inode*) ; 
 int /*<<< orphan*/  integrity_audit_msg (int /*<<< orphan*/ ,struct inode*,unsigned char const*,char const*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ima_template_entry*) ; 
 struct ima_template_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 

void ima_add_violation(struct inode *inode, const unsigned char *filename,
		       const char *op, const char *cause)
{
	struct ima_template_entry *entry;
	int violation = 1;
	int result;

	/* can overflow, only indicator */
	atomic_long_inc(&ima_htable.violations);

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		result = -ENOMEM;
		goto err_out;
	}
	memset(&entry->template, 0, sizeof(entry->template));
	strncpy(entry->template.file_name, filename, IMA_EVENT_NAME_LEN_MAX);
	result = ima_store_template(entry, violation, inode);
	if (result < 0)
		kfree(entry);
err_out:
	integrity_audit_msg(AUDIT_INTEGRITY_PCR, inode, filename,
			    op, cause, result, 0);
}
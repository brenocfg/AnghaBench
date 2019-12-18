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
typedef  int /*<<< orphan*/  u32 ;
struct netlbl_audit {int dummy; } ;
struct cipso_v4_doi {int /*<<< orphan*/  rcu; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; } ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_MAC_CIPSOV4_DEL ; 
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cipso_v4_cache_invalidate () ; 
 int /*<<< orphan*/  cipso_v4_doi_free_rcu ; 
 int /*<<< orphan*/  cipso_v4_doi_list_lock ; 
 struct cipso_v4_doi* cipso_v4_doi_search (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 struct audit_buffer* netlbl_audit_start (int /*<<< orphan*/ ,struct netlbl_audit*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int cipso_v4_doi_remove(u32 doi, struct netlbl_audit *audit_info)
{
	int ret_val;
	struct cipso_v4_doi *doi_def;
	struct audit_buffer *audit_buf;

	spin_lock(&cipso_v4_doi_list_lock);
	doi_def = cipso_v4_doi_search(doi);
	if (doi_def == NULL) {
		spin_unlock(&cipso_v4_doi_list_lock);
		ret_val = -ENOENT;
		goto doi_remove_return;
	}
	if (!atomic_dec_and_test(&doi_def->refcount)) {
		spin_unlock(&cipso_v4_doi_list_lock);
		ret_val = -EBUSY;
		goto doi_remove_return;
	}
	list_del_rcu(&doi_def->list);
	spin_unlock(&cipso_v4_doi_list_lock);

	cipso_v4_cache_invalidate();
	call_rcu(&doi_def->rcu, cipso_v4_doi_free_rcu);
	ret_val = 0;

doi_remove_return:
	audit_buf = netlbl_audit_start(AUDIT_MAC_CIPSOV4_DEL, audit_info);
	if (audit_buf != NULL) {
		audit_log_format(audit_buf,
				 " cipso_doi=%u res=%u",
				 doi, ret_val == 0 ? 1 : 0);
		audit_log_end(audit_buf);
	}

	return ret_val;
}
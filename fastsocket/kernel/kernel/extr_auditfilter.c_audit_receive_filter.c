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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {int /*<<< orphan*/  rule; } ;
struct audit_netlink_list {int pid; int /*<<< orphan*/  q; } ;
struct audit_entry {int /*<<< orphan*/  rule; } ;

/* Variables and functions */
#define  AUDIT_ADD 133 
#define  AUDIT_ADD_RULE 132 
#define  AUDIT_DEL 131 
#define  AUDIT_DEL_RULE 130 
#define  AUDIT_LIST 129 
#define  AUDIT_LIST_RULES 128 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int audit_add_rule (struct task_struct*) ; 
 struct task_struct* audit_data_to_entry (void*,size_t) ; 
 int audit_del_rule (struct task_struct*) ; 
 int /*<<< orphan*/  audit_filter_mutex ; 
 int /*<<< orphan*/  audit_free_rule (struct task_struct*) ; 
 int /*<<< orphan*/  audit_list (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_list_rules (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_log_rule_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 struct task_struct* audit_rule_to_entry (void*) ; 
 int /*<<< orphan*/  audit_send_list ; 
 int /*<<< orphan*/  kfree (struct audit_netlink_list*) ; 
 struct audit_netlink_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct audit_netlink_list*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

int audit_receive_filter(int type, int pid, int uid, int seq, void *data,
			 size_t datasz, uid_t loginuid, u32 sessionid, u32 sid)
{
	struct task_struct *tsk;
	struct audit_netlink_list *dest;
	int err = 0;
	struct audit_entry *entry;

	switch (type) {
	case AUDIT_LIST:
	case AUDIT_LIST_RULES:
		/* We can't just spew out the rules here because we might fill
		 * the available socket buffer space and deadlock waiting for
		 * auditctl to read from it... which isn't ever going to
		 * happen if we're actually running in the context of auditctl
		 * trying to _send_ the stuff */

		dest = kmalloc(sizeof(struct audit_netlink_list), GFP_KERNEL);
		if (!dest)
			return -ENOMEM;
		dest->pid = pid;
		skb_queue_head_init(&dest->q);

		mutex_lock(&audit_filter_mutex);
		if (type == AUDIT_LIST)
			audit_list(pid, seq, &dest->q);
		else
			audit_list_rules(pid, seq, &dest->q);
		mutex_unlock(&audit_filter_mutex);

		tsk = kthread_run(audit_send_list, dest, "audit_send_list");
		if (IS_ERR(tsk)) {
			skb_queue_purge(&dest->q);
			kfree(dest);
			err = PTR_ERR(tsk);
		}
		break;
	case AUDIT_ADD:
	case AUDIT_ADD_RULE:
		if (type == AUDIT_ADD)
			entry = audit_rule_to_entry(data);
		else
			entry = audit_data_to_entry(data, datasz);
		if (IS_ERR(entry))
			return PTR_ERR(entry);

		err = audit_add_rule(entry);
		audit_log_rule_change(loginuid, sessionid, sid, "add rule",
				      &entry->rule, !err);

		if (err)
			audit_free_rule(entry);
		break;
	case AUDIT_DEL:
	case AUDIT_DEL_RULE:
		if (type == AUDIT_DEL)
			entry = audit_rule_to_entry(data);
		else
			entry = audit_data_to_entry(data, datasz);
		if (IS_ERR(entry))
			return PTR_ERR(entry);

		err = audit_del_rule(entry);
		audit_log_rule_change(loginuid, sessionid, sid, "remove rule",
				      &entry->rule, !err);

		audit_free_rule(entry);
		break;
	default:
		return -EINVAL;
	}

	return err;
}
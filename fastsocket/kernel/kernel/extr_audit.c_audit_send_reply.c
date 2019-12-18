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
struct task_struct {int dummy; } ;
struct sk_buff {int dummy; } ;
struct audit_reply {int pid; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct task_struct*) ; 
 struct sk_buff* audit_make_reply (int,int,int,int,int,void*,int) ; 
 int /*<<< orphan*/  audit_send_reply_thread ; 
 int /*<<< orphan*/  kfree (struct audit_reply*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct audit_reply* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct audit_reply*,char*) ; 

void audit_send_reply(int pid, int seq, int type, int done, int multi,
		      void *payload, int size)
{
	struct sk_buff *skb;
	struct task_struct *tsk;
	struct audit_reply *reply = kmalloc(sizeof(struct audit_reply),
					    GFP_KERNEL);

	if (!reply)
		return;

	skb = audit_make_reply(pid, seq, type, done, multi, payload, size);
	if (!skb)
		goto out;

	reply->pid = pid;
	reply->skb = skb;

	tsk = kthread_run(audit_send_reply_thread, reply, "audit_send_reply");
	if (!IS_ERR(tsk))
		return;
	kfree_skb(skb);
out:
	kfree(reply);
}
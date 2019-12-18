#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nlmsghdr {scalar_t__ nlmsg_len; } ;
struct audit_buffer {TYPE_1__* skb; } ;
struct TYPE_4__ {scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ NLMSG_SPACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_buffer_free (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_lost (char*) ; 
 scalar_t__ audit_pid ; 
 int /*<<< orphan*/  audit_printk_skb (TYPE_1__*) ; 
 int /*<<< orphan*/  audit_rate_check () ; 
 int /*<<< orphan*/  audit_skb_queue ; 
 int /*<<< orphan*/  kauditd_wait ; 
 struct nlmsghdr* nlmsg_hdr (TYPE_1__*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void audit_log_end(struct audit_buffer *ab)
{
	if (!ab)
		return;
	if (!audit_rate_check()) {
		audit_log_lost("rate limit exceeded");
	} else {
		struct nlmsghdr *nlh = nlmsg_hdr(ab->skb);
		nlh->nlmsg_len = ab->skb->len - NLMSG_SPACE(0);

		if (audit_pid) {
			skb_queue_tail(&audit_skb_queue, ab->skb);
			wake_up_interruptible(&kauditd_wait);
		} else {
			audit_printk_skb(ab->skb);
		}
		ab->skb = NULL;
	}
	audit_buffer_free(ab);
}
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
struct nf_queue_entry {int dummy; } ;
struct ipq_verdict_msg {int value; unsigned int data_len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int NF_DROP ; 
 int NF_MAX_VERDICT ; 
 struct nf_queue_entry* ipq_find_dequeue_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ ipq_mangle_ipv4 (struct ipq_verdict_msg*,struct nf_queue_entry*) ; 
 int /*<<< orphan*/  nf_reinject (struct nf_queue_entry*,int) ; 

__attribute__((used)) static int
ipq_set_verdict(struct ipq_verdict_msg *vmsg, unsigned int len)
{
	struct nf_queue_entry *entry;

	if (vmsg->value > NF_MAX_VERDICT)
		return -EINVAL;

	entry = ipq_find_dequeue_entry(vmsg->id);
	if (entry == NULL)
		return -ENOENT;
	else {
		int verdict = vmsg->value;

		if (vmsg->data_len && vmsg->data_len == len)
			if (ipq_mangle_ipv4(vmsg, entry) < 0)
				verdict = NF_DROP;

		nf_reinject(entry, verdict);
		return 0;
	}
}
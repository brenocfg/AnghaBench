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
struct ipmi_smi_msg {int data_size; int /*<<< orphan*/ * data; int /*<<< orphan*/  msgid; } ;
struct TYPE_2__ {int data_len; int /*<<< orphan*/  data; } ;
struct ipmi_recv_msg {TYPE_1__ msg; } ;
typedef  int /*<<< orphan*/  ipmi_smi_t ;

/* Variables and functions */
 int /*<<< orphan*/  STORE_SEQ_IN_MSGID (unsigned char,long) ; 
 struct ipmi_smi_msg* ipmi_alloc_smi_msg () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static struct ipmi_smi_msg *
smi_from_recv_msg(ipmi_smi_t intf, struct ipmi_recv_msg *recv_msg,
		  unsigned char seq, long seqid)
{
	struct ipmi_smi_msg *smi_msg = ipmi_alloc_smi_msg();
	if (!smi_msg)
		/*
		 * If we can't allocate the message, then just return, we
		 * get 4 retries, so this should be ok.
		 */
		return NULL;

	memcpy(smi_msg->data, recv_msg->msg.data, recv_msg->msg.data_len);
	smi_msg->data_size = recv_msg->msg.data_len;
	smi_msg->msgid = STORE_SEQ_IN_MSGID(seq, seqid);

#ifdef DEBUG_MSGING
	{
		int m;
		printk("Resend: ");
		for (m = 0; m < smi_msg->data_size; m++)
			printk(" %2.2x", smi_msg->data[m]);
		printk("\n");
	}
#endif
	return smi_msg;
}
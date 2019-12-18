#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_table {int /*<<< orphan*/  recv_msg; int /*<<< orphan*/  inuse; } ;
typedef  TYPE_1__* ipmi_smi_t ;
struct TYPE_3__ {struct seq_table* seq_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_ERR_UNSPECIFIED ; 
 int IPMI_IPMB_NUM_SEQ ; 
 int /*<<< orphan*/  deliver_err_response (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_smi_msgs(ipmi_smi_t intf)
{
	int              i;
	struct seq_table *ent;

	/* No need for locks, the interface is down. */
	for (i = 0; i < IPMI_IPMB_NUM_SEQ; i++) {
		ent = &(intf->seq_table[i]);
		if (!ent->inuse)
			continue;
		deliver_err_response(ent->recv_msg, IPMI_ERR_UNSPECIFIED);
	}
}
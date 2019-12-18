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
struct ipmi_smi_msg {int /*<<< orphan*/ * user_data; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_smi_msg ; 
 struct ipmi_smi_msg* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_msg_inuse_count ; 

struct ipmi_smi_msg *ipmi_alloc_smi_msg(void)
{
	struct ipmi_smi_msg *rv;
	rv = kmalloc(sizeof(struct ipmi_smi_msg), GFP_ATOMIC);
	if (rv) {
		rv->done = free_smi_msg;
		rv->user_data = NULL;
		atomic_inc(&smi_msg_inuse_count);
	}
	return rv;
}
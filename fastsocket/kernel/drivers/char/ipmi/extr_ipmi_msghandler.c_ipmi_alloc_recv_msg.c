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
struct ipmi_recv_msg {int /*<<< orphan*/  done; int /*<<< orphan*/ * user; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_recv_msg ; 
 struct ipmi_recv_msg* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recv_msg_inuse_count ; 

__attribute__((used)) static struct ipmi_recv_msg *ipmi_alloc_recv_msg(void)
{
	struct ipmi_recv_msg *rv;

	rv = kmalloc(sizeof(struct ipmi_recv_msg), GFP_ATOMIC);
	if (rv) {
		rv->user = NULL;
		rv->done = free_recv_msg;
		atomic_inc(&recv_msg_inuse_count);
	}
	return rv;
}
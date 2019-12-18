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
struct msg_msgseg {struct msg_msgseg* next; } ;
struct msg_msg {struct msg_msg* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct msg_msgseg*) ; 
 int /*<<< orphan*/  security_msg_msg_free (struct msg_msgseg*) ; 

void free_msg(struct msg_msg *msg)
{
	struct msg_msgseg *seg;

	security_msg_msg_free(msg);

	seg = msg->next;
	kfree(msg);
	while (seg != NULL) {
		struct msg_msgseg *tmp = seg->next;
		kfree(seg);
		seg = tmp;
	}
}
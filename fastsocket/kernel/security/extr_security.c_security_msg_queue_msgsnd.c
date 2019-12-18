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
struct msg_queue {int dummy; } ;
struct msg_msg {int dummy; } ;
struct TYPE_2__ {int (* msg_queue_msgsnd ) (struct msg_queue*,struct msg_msg*,int) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct msg_queue*,struct msg_msg*,int) ; 

int security_msg_queue_msgsnd(struct msg_queue *msq,
			       struct msg_msg *msg, int msqflg)
{
	return security_ops->msg_queue_msgsnd(msq, msg, msqflg);
}
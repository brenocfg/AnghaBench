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
struct TYPE_2__ {int /*<<< orphan*/  (* msg_queue_free_security ) (struct msg_queue*) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int /*<<< orphan*/  stub1 (struct msg_queue*) ; 

void security_msg_queue_free(struct msg_queue *msq)
{
	security_ops->msg_queue_free_security(msq);
}
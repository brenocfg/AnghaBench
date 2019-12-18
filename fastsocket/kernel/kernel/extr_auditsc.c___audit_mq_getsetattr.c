#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mq_attr {int dummy; } ;
struct TYPE_3__ {struct mq_attr mqstat; int /*<<< orphan*/  mqdes; } ;
struct audit_context {int /*<<< orphan*/  type; TYPE_1__ mq_getsetattr; } ;
typedef  int /*<<< orphan*/  mqd_t ;
struct TYPE_4__ {struct audit_context* audit_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_MQ_GETSETATTR ; 
 TYPE_2__* current ; 

void __audit_mq_getsetattr(mqd_t mqdes, struct mq_attr *mqstat)
{
	struct audit_context *context = current->audit_context;
	context->mq_getsetattr.mqdes = mqdes;
	context->mq_getsetattr.mqstat = *mqstat;
	context->type = AUDIT_MQ_GETSETATTR;
}
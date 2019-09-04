#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_cond_t ;
struct TYPE_5__ {scalar_t__ pthreadCondT_; } ;
struct TYPE_6__ {TYPE_1__ org_xmlvm_runtime_Condition; } ;
struct TYPE_7__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_Condition ;

/* Variables and functions */

pthread_cond_t* getConditionPtr(org_xmlvm_runtime_Condition* me)
{
    return (pthread_cond_t*)(me->fields.org_xmlvm_runtime_Condition.pthreadCondT_);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_cond_t ;
struct TYPE_4__ {int /*<<< orphan*/  pthreadCondT_; } ;
struct TYPE_5__ {TYPE_1__ org_xmlvm_runtime_Condition; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_Condition ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  XMLVM_FINALIZE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getConditionPtr (scalar_t__) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  nativeConditionCleanup ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void org_xmlvm_runtime_Condition_initNativeConditionInstance__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_Condition_initNativeConditionInstance__]
    ((org_xmlvm_runtime_Condition*)me)->fields.org_xmlvm_runtime_Condition.pthreadCondT_ = malloc(sizeof(pthread_cond_t));
    pthread_cond_init(getConditionPtr(me), NULL);

    // Register a finalizer for native cleanup
    XMLVM_FINALIZE(me, nativeConditionCleanup);
    //XMLVM_END_NATIVE
}
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
typedef  int /*<<< orphan*/  org_xmlvm_runtime_Condition ;
typedef  int /*<<< orphan*/  java_util_Map ;
typedef  int /*<<< orphan*/  java_lang_Thread_State ;
typedef  int /*<<< orphan*/  java_lang_ThreadGroup ;
struct TYPE_4__ {int /*<<< orphan*/ * action_; scalar_t__ nativeThreadId_; int /*<<< orphan*/ * threadLocalMap_; int /*<<< orphan*/ * waitingCondition_; scalar_t__ interrupted_; int /*<<< orphan*/ * threadState_; int /*<<< orphan*/ * threadGroup_; int /*<<< orphan*/ * targetRunnable_; scalar_t__ alive_; scalar_t__ daemon_; scalar_t__ priority_; int /*<<< orphan*/ * threadName_; scalar_t__ threadId_; int /*<<< orphan*/ * ptBuffers_; int /*<<< orphan*/ * xmlvmException_; int /*<<< orphan*/ * xmlvmExceptionEnv_; } ;
struct TYPE_5__ {TYPE_1__ java_lang_Thread; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_Thread ;
typedef  int /*<<< orphan*/  java_lang_String ;
typedef  int /*<<< orphan*/  java_lang_Runnable ;
typedef  int /*<<< orphan*/  java_lang_Object ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_lang_Object (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_java_lang_Thread(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_lang_Object(me, 0 || derivedClassWillRegisterFinalizer);
    ((java_lang_Thread*) me)->fields.java_lang_Thread.xmlvmExceptionEnv_ = (java_lang_Object*) JAVA_NULL;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.xmlvmException_ = (java_lang_Object*) JAVA_NULL;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.ptBuffers_ = (java_lang_Object*) JAVA_NULL;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.threadId_ = 0;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.threadName_ = (java_lang_String*) JAVA_NULL;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.priority_ = 0;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.daemon_ = 0;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.alive_ = 0;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.targetRunnable_ = (java_lang_Runnable*) JAVA_NULL;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.threadGroup_ = (java_lang_ThreadGroup*) JAVA_NULL;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.threadState_ = (java_lang_Thread_State*) JAVA_NULL;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.interrupted_ = 0;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.waitingCondition_ = (org_xmlvm_runtime_Condition*) JAVA_NULL;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.threadLocalMap_ = (java_util_Map*) JAVA_NULL;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.nativeThreadId_ = 0;
    ((java_lang_Thread*) me)->fields.java_lang_Thread.action_ = (java_lang_Runnable*) JAVA_NULL;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_java_lang_Thread]
    //XMLVM_END_WRAPPER
}
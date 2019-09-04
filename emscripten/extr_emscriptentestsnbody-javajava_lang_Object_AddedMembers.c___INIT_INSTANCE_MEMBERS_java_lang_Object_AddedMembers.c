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
typedef  int /*<<< orphan*/  org_xmlvm_runtime_Mutex ;
typedef  int /*<<< orphan*/  java_util_List ;
typedef  int /*<<< orphan*/  java_lang_Thread ;
struct TYPE_4__ {scalar_t__ notifyAllMaxIndex_; int /*<<< orphan*/ * waitingConditions_; int /*<<< orphan*/ * instanceMutex_; int /*<<< orphan*/ * owningThread_; scalar_t__ recursiveLocks_; } ;
struct TYPE_5__ {TYPE_1__ java_lang_Object_AddedMembers; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_Object_AddedMembers ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_lang_Object (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_java_lang_Object_AddedMembers(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_lang_Object(me, 0 || derivedClassWillRegisterFinalizer);
    ((java_lang_Object_AddedMembers*) me)->fields.java_lang_Object_AddedMembers.recursiveLocks_ = 0;
    ((java_lang_Object_AddedMembers*) me)->fields.java_lang_Object_AddedMembers.owningThread_ = (java_lang_Thread*) JAVA_NULL;
    ((java_lang_Object_AddedMembers*) me)->fields.java_lang_Object_AddedMembers.instanceMutex_ = (org_xmlvm_runtime_Mutex*) JAVA_NULL;
    ((java_lang_Object_AddedMembers*) me)->fields.java_lang_Object_AddedMembers.waitingConditions_ = (java_util_List*) JAVA_NULL;
    ((java_lang_Object_AddedMembers*) me)->fields.java_lang_Object_AddedMembers.notifyAllMaxIndex_ = 0;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_java_lang_Object_AddedMembers]
    //XMLVM_END_WRAPPER
}
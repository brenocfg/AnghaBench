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
struct TYPE_4__ {int /*<<< orphan*/ * synchronizedObject_; int /*<<< orphan*/ * pthreadCondT_; } ;
struct TYPE_5__ {TYPE_1__ org_xmlvm_runtime_Condition; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_Condition ;
typedef  int /*<<< orphan*/  java_lang_Object ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_lang_Object (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_org_xmlvm_runtime_Condition(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_lang_Object(me, 0 || derivedClassWillRegisterFinalizer);
    ((org_xmlvm_runtime_Condition*) me)->fields.org_xmlvm_runtime_Condition.pthreadCondT_ = (java_lang_Object*) JAVA_NULL;
    ((org_xmlvm_runtime_Condition*) me)->fields.org_xmlvm_runtime_Condition.synchronizedObject_ = (java_lang_Object*) JAVA_NULL;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_org_xmlvm_runtime_Condition]
    //XMLVM_END_WRAPPER
}
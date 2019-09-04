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
typedef  int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray ;
struct TYPE_4__ {int /*<<< orphan*/ * parameterAnnotations_; int /*<<< orphan*/ * annotations_; int /*<<< orphan*/ * signature_; scalar_t__ modifiers_; int /*<<< orphan*/ * exceptionTypes_; int /*<<< orphan*/ * parameterTypes_; scalar_t__ slot_; int /*<<< orphan*/ * address_; int /*<<< orphan*/ * clazz_; int /*<<< orphan*/ * name_; } ;
struct TYPE_5__ {TYPE_1__ java_lang_reflect_Method; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_reflect_Method ;
typedef  int /*<<< orphan*/  java_lang_String ;
typedef  int /*<<< orphan*/  java_lang_Object ;
typedef  int /*<<< orphan*/  java_lang_Class ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_lang_reflect_AccessibleObject (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_java_lang_reflect_Method(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_lang_reflect_AccessibleObject(me, 0 || derivedClassWillRegisterFinalizer);
    ((java_lang_reflect_Method*) me)->fields.java_lang_reflect_Method.name_ = (java_lang_String*) JAVA_NULL;
    ((java_lang_reflect_Method*) me)->fields.java_lang_reflect_Method.clazz_ = (java_lang_Class*) JAVA_NULL;
    ((java_lang_reflect_Method*) me)->fields.java_lang_reflect_Method.address_ = (java_lang_Object*) JAVA_NULL;
    ((java_lang_reflect_Method*) me)->fields.java_lang_reflect_Method.slot_ = 0;
    ((java_lang_reflect_Method*) me)->fields.java_lang_reflect_Method.parameterTypes_ = (org_xmlvm_runtime_XMLVMArray*) JAVA_NULL;
    ((java_lang_reflect_Method*) me)->fields.java_lang_reflect_Method.exceptionTypes_ = (org_xmlvm_runtime_XMLVMArray*) JAVA_NULL;
    ((java_lang_reflect_Method*) me)->fields.java_lang_reflect_Method.modifiers_ = 0;
    ((java_lang_reflect_Method*) me)->fields.java_lang_reflect_Method.signature_ = (java_lang_String*) JAVA_NULL;
    ((java_lang_reflect_Method*) me)->fields.java_lang_reflect_Method.annotations_ = (org_xmlvm_runtime_XMLVMArray*) JAVA_NULL;
    ((java_lang_reflect_Method*) me)->fields.java_lang_reflect_Method.parameterAnnotations_ = (org_xmlvm_runtime_XMLVMArray*) JAVA_NULL;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_java_lang_reflect_Method]
    //XMLVM_END_WRAPPER
}
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
struct TYPE_4__ {scalar_t__ firstK_; int /*<<< orphan*/ * uArray_; scalar_t__ getCount_; scalar_t__ setCount_; } ;
struct TYPE_5__ {TYPE_1__ org_apache_harmony_luni_util_NumberConverter; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_apache_harmony_luni_util_NumberConverter ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_lang_Object (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_org_apache_harmony_luni_util_NumberConverter(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_lang_Object(me, 0 || derivedClassWillRegisterFinalizer);
    ((org_apache_harmony_luni_util_NumberConverter*) me)->fields.org_apache_harmony_luni_util_NumberConverter.setCount_ = 0;
    ((org_apache_harmony_luni_util_NumberConverter*) me)->fields.org_apache_harmony_luni_util_NumberConverter.getCount_ = 0;
    ((org_apache_harmony_luni_util_NumberConverter*) me)->fields.org_apache_harmony_luni_util_NumberConverter.uArray_ = (org_xmlvm_runtime_XMLVMArray*) JAVA_NULL;
    ((org_apache_harmony_luni_util_NumberConverter*) me)->fields.org_apache_harmony_luni_util_NumberConverter.firstK_ = 0;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_org_apache_harmony_luni_util_NumberConverter]
    //XMLVM_END_WRAPPER
}
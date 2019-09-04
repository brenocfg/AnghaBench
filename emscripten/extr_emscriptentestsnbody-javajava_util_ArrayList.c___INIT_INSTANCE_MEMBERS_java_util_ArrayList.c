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
struct TYPE_4__ {int /*<<< orphan*/ * array_; scalar_t__ size_; scalar_t__ firstIndex_; } ;
struct TYPE_5__ {TYPE_1__ java_util_ArrayList; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_util_ArrayList ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_util_AbstractList (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_java_util_ArrayList(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_util_AbstractList(me, 0 || derivedClassWillRegisterFinalizer);
    ((java_util_ArrayList*) me)->fields.java_util_ArrayList.firstIndex_ = 0;
    ((java_util_ArrayList*) me)->fields.java_util_ArrayList.size_ = 0;
    ((java_util_ArrayList*) me)->fields.java_util_ArrayList.array_ = (org_xmlvm_runtime_XMLVMArray*) JAVA_NULL;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_java_util_ArrayList]
    //XMLVM_END_WRAPPER
}
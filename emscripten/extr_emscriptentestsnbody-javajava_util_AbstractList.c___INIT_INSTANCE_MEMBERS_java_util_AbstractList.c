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
struct TYPE_4__ {scalar_t__ modCount_; } ;
struct TYPE_5__ {TYPE_1__ java_util_AbstractList; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_util_AbstractList ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_util_AbstractCollection (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_java_util_AbstractList(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_util_AbstractCollection(me, 0 || derivedClassWillRegisterFinalizer);
    ((java_util_AbstractList*) me)->fields.java_util_AbstractList.modCount_ = 0;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_java_util_AbstractList]
    //XMLVM_END_WRAPPER
}
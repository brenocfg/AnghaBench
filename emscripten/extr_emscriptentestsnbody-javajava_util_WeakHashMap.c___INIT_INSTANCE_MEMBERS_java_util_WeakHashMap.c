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
struct TYPE_4__ {scalar_t__ modCount_; scalar_t__ threshold_; scalar_t__ loadFactor_; int /*<<< orphan*/ * elementData_; scalar_t__ elementCount_; int /*<<< orphan*/ * referenceQueue_; } ;
struct TYPE_5__ {TYPE_1__ java_util_WeakHashMap; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_util_WeakHashMap ;
typedef  int /*<<< orphan*/  java_lang_ref_ReferenceQueue ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_util_AbstractMap (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_java_util_WeakHashMap(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_util_AbstractMap(me, 0 || derivedClassWillRegisterFinalizer);
    ((java_util_WeakHashMap*) me)->fields.java_util_WeakHashMap.referenceQueue_ = (java_lang_ref_ReferenceQueue*) JAVA_NULL;
    ((java_util_WeakHashMap*) me)->fields.java_util_WeakHashMap.elementCount_ = 0;
    ((java_util_WeakHashMap*) me)->fields.java_util_WeakHashMap.elementData_ = (org_xmlvm_runtime_XMLVMArray*) JAVA_NULL;
    ((java_util_WeakHashMap*) me)->fields.java_util_WeakHashMap.loadFactor_ = 0;
    ((java_util_WeakHashMap*) me)->fields.java_util_WeakHashMap.threshold_ = 0;
    ((java_util_WeakHashMap*) me)->fields.java_util_WeakHashMap.modCount_ = 0;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_java_util_WeakHashMap]
    //XMLVM_END_WRAPPER
}
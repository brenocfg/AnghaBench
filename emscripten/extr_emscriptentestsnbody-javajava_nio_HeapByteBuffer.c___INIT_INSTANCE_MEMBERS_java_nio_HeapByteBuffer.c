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
struct TYPE_4__ {scalar_t__ offset_; int /*<<< orphan*/ * backingArray_; } ;
struct TYPE_5__ {TYPE_1__ java_nio_HeapByteBuffer; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_nio_HeapByteBuffer ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_nio_ByteBuffer (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_java_nio_HeapByteBuffer(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_nio_ByteBuffer(me, 0 || derivedClassWillRegisterFinalizer);
    ((java_nio_HeapByteBuffer*) me)->fields.java_nio_HeapByteBuffer.backingArray_ = (org_xmlvm_runtime_XMLVMArray*) JAVA_NULL;
    ((java_nio_HeapByteBuffer*) me)->fields.java_nio_HeapByteBuffer.offset_ = 0;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_java_nio_HeapByteBuffer]
    //XMLVM_END_WRAPPER
}
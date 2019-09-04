#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int length_; scalar_t__ array_; scalar_t__ type_; } ;
struct TYPE_6__ {TYPE_2__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_8__ {TYPE_1__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_XMLVMArray ;
struct TYPE_9__ {int sizeOfBaseType; scalar_t__ useAtomicMalloc; } ;
typedef  TYPE_4__ TYPE_INFO ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  int JAVA_INT ;

/* Variables and functions */
 scalar_t__ XMLVMArray_createSingleDimensionWithData (scalar_t__,int,scalar_t__) ; 
 TYPE_4__ XMLVMArray_getTypeInfo (scalar_t__) ; 
 scalar_t__ XMLVM_ATOMIC_MALLOC (int) ; 
 scalar_t__ XMLVM_MALLOC (int) ; 
 int /*<<< orphan*/  XMLVM_MEMCPY (scalar_t__,scalar_t__,int) ; 

JAVA_OBJECT org_xmlvm_runtime_XMLVMArray_clone__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_XMLVMArray_clone__]
    org_xmlvm_runtime_XMLVMArray* thiz = (org_xmlvm_runtime_XMLVMArray*) me;
    JAVA_OBJECT type = thiz->fields.org_xmlvm_runtime_XMLVMArray.type_;
    JAVA_INT length = thiz->fields.org_xmlvm_runtime_XMLVMArray.length_;
    JAVA_OBJECT data = thiz->fields.org_xmlvm_runtime_XMLVMArray.array_;
    TYPE_INFO info = XMLVMArray_getTypeInfo(type);
    int sizeOfArrayInBytes = info.sizeOfBaseType * length;
    JAVA_OBJECT copyData = info.useAtomicMalloc ? XMLVM_ATOMIC_MALLOC(sizeOfArrayInBytes) : XMLVM_MALLOC(sizeOfArrayInBytes);
    XMLVM_MEMCPY(copyData, data, sizeOfArrayInBytes);
    return XMLVMArray_createSingleDimensionWithData(type, length, copyData);
    //XMLVM_END_NATIVE
}